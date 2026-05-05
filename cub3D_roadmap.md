# 🗺️ cub3D — Roadmap complète (ta partie : raycasting + mouvements)

> **Légende :**
> - 🟢 Tu peux faire ça seul
> - 🔴 Tu as besoin de ton mate
> - 🟡 Tu peux commencer, mais à finaliser avec ton mate

---

## PHASE 0 — Setup du projet (jour 1)
🟢 **Indépendant**

### 0.1 — Structure des dossiers
```
cub3D/
├── Makefile
├── includes/
│   └── cub3d.h
├── srcs/
│   ├── main.c
│   ├── mlx_init.c
│   ├── hooks.c
│   ├── raycasting.c
│   ├── player.c
│   └── render.c
├── textures/
└── maps/
    └── test.cub
```

### 0.2 — Makefile
- Règles : `all`, `clean`, `fclean`, `re`, `bonus`
- Flags : `-Wall -Wextra -Werror`
- Lier : `-lmlx -lXext -lX11 -lm` (Linux) ou `-lmlx -framework OpenGL -framework AppKit -lm` (Mac)

### 0.3 — Structures de base (à définir MAINTENANT avec ton mate)

⚠️ **Point de synchronisation critique avec ton mate.**
Ces structs sont le contrat entre vos deux parties. Définissez-les ensemble avant de coder.

```c
/* includes/cub3d.h */

typedef struct s_img {
    void    *img_ptr;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   t_img;

typedef struct s_player {
    double  x;         // position dans la map (en cases)
    double  y;
    double  dir_x;     // vecteur direction (longueur 1)
    double  dir_y;
    double  plane_x;   // vecteur plan caméra (perpendiculaire à dir)
    double  plane_y;
    double  move_speed;
    double  rot_speed;
}   t_player;

typedef struct s_map {
    char    **grid;    // grille 2D
    int     width;
    int     height;
}   t_map;

typedef struct s_game {
    void        *mlx;
    void        *win;
    t_img       screen;      // image buffer principale
    t_img       textures[4]; // 0=NO, 1=SO, 2=EA, 3=WE
    t_player    player;
    t_map       map;
    int         floor_color;
    int         ceil_color;
}   t_game;
```

---

## PHASE 1 — Fenêtre et hooks (jour 1-2)
🟢 **Indépendant** — tu connais déjà ça depuis so_long

### 1.1 — Initialiser mlx et la fenêtre
```c
// mlx_init.c
game->mlx = mlx_init();
game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");

// Créer le buffer image (jamais mlx_pixel_put, trop lent)
game->screen.img_ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
game->screen.addr = mlx_get_data_addr(
    game->screen.img_ptr,
    &game->screen.bpp,
    &game->screen.line_len,
    &game->screen.endian
);
```

### 1.2 — Hooks
```c
// hooks.c
mlx_hook(game->win, 2, 1L<<0, key_press, game);    // KeyPress
mlx_hook(game->win, 17, 0, close_window, game);     // clic croix rouge
mlx_loop_hook(game->mlx, game_loop, game);           // chaque frame
mlx_loop(game->mlx);
```

### 1.3 — Fermeture propre (ESC + croix rouge)
```c
int close_window(t_game *game)
{
    // free map grid
    // destroy images mlx (textures + screen)
    // mlx_destroy_window
    // exit(0)
}

int key_press(int key, t_game *game)
{
    if (key == 65307) // ESC
        close_window(game);
    return (0);
}
```

### 1.4 — Fonction pour écrire un pixel dans le buffer
```c
void    put_pixel(t_img *img, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return ;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}
```

✅ **Test phase 1 :** fenêtre noire qui s'ouvre, ESC et croix rouge ferment proprement.

---

## PHASE 2 — Map hardcodée temporaire (jour 2)
🟢 **Indépendant** — pour ne pas attendre le parsing de ton mate

### 2.1 — Créer une fausse map en dur
```c
void    init_test_map(t_game *game)
{
    static char *grid[] = {
        "111111111",
        "100000001",
        "101000101",
        "100000001",
        "111N00111",
        "100000001",
        "101000101",
        "100000001",
        "111111111",
        NULL
    };
    game->map.grid = grid;
    game->map.width = 9;
    game->map.height = 9;
}
```

### 2.2 — Initialiser le joueur selon la map
- `N` dans la map → `dir_x = 0, dir_y = -1, plane_x = 0.66, plane_y = 0`
- `S` → `dir_x = 0, dir_y = 1, plane_x = -0.66, plane_y = 0`
- `E` → `dir_x = 1, dir_y = 0, plane_x = 0, plane_y = 0.66`
- `W` → `dir_x = -1, dir_y = 0, plane_x = 0, plane_y = -0.66`

```c
// Le 0.66 = tan(FOV/2), avec FOV = 66°
game->player.x = col + 0.5; // centre de la case
game->player.y = row + 0.5;
game->player.move_speed = 0.05;
game->player.rot_speed = 0.03;
```

---

## PHASE 3 — Raycasting (jour 3-5)
🟢 **Indépendant** — c'est ta partie principale

### 3.1 — Théorie essentielle

Le principe : pour **chaque colonne de pixels** de la fenêtre, on lance un rayon.
Le rayon part de la position du joueur dans une direction calculée selon l'angle de la caméra.
On détermine à quelle distance il touche un mur, puis on calcule la hauteur de la colonne à dessiner.

```
camera_x = 2 * x / WIN_WIDTH - 1   // va de -1 (gauche) à +1 (droite)
ray_dir_x = dir_x + plane_x * camera_x
ray_dir_y = dir_y + plane_y * camera_y
```

### 3.2 — Algorithme DDA (Digital Differential Analysis)

```c
// raycasting.c - pour chaque colonne x de 0 à WIN_WIDTH

// 1. Calculer la direction du rayon
double camera_x = 2 * x / (double)WIN_WIDTH - 1;
double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

// 2. Case de départ
int map_x = (int)game->player.x;
int map_y = (int)game->player.y;

// 3. Distance entre deux intersections de grille (delta)
double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);

// 4. Direction du pas + distance initiale
int step_x, step_y;
double side_dist_x, side_dist_y;

if (ray_dir_x < 0) { step_x = -1; side_dist_x = (game->player.x - map_x) * delta_dist_x; }
else               { step_x =  1; side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x; }
if (ray_dir_y < 0) { step_y = -1; side_dist_y = (game->player.y - map_y) * delta_dist_y; }
else               { step_y =  1; side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y; }

// 5. Boucle DDA — avancer jusqu'à toucher un mur
int side; // 0 = mur X (NS), 1 = mur Y (EO)
while (game->map.grid[map_y][map_x] != '1')
{
    if (side_dist_x < side_dist_y) { side_dist_x += delta_dist_x; map_x += step_x; side = 0; }
    else                           { side_dist_y += delta_dist_y; map_y += step_y; side = 1; }
}

// 6. Distance perpendiculaire (évite l'effet fisheye !)
double perp_wall_dist;
if (side == 0) perp_wall_dist = side_dist_x - delta_dist_x;
else           perp_wall_dist = side_dist_y - delta_dist_y;

// 7. Hauteur de la colonne à dessiner
int line_height = (int)(WIN_HEIGHT / perp_wall_dist);
int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
int draw_end   =  line_height / 2 + WIN_HEIGHT / 2;
if (draw_start < 0) draw_start = 0;
if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;
```

### 3.3 — Rendu sans texture (pour valider la géo d'abord)

```c
// Choisir une couleur selon le côté touché
int color;
if (side == 0) color = 0xFF0000; // rouge : mur face N ou S
else           color = 0xAA0000; // rouge foncé : mur face E ou W

// Dessiner le plafond, le mur, le sol pour cette colonne
for (int y = 0; y < WIN_HEIGHT; y++)
{
    if (y < draw_start)      put_pixel(&game->screen, x, y, game->ceil_color);
    else if (y <= draw_end)  put_pixel(&game->screen, x, y, color);
    else                     put_pixel(&game->screen, x, y, game->floor_color);
}
```

### 3.4 — Game loop
```c
int game_loop(t_game *game)
{
    handle_movement(game);           // lire les touches et bouger
    raycast(game);                   // remplir le buffer screen
    mlx_put_image_to_window(game->mlx, game->win, game->screen.img_ptr, 0, 0);
    return (0);
}
```

✅ **Test phase 3 :** tu dois voir un labyrinthe en 3D avec des couleurs unies. Pas de texture, mais la géométrie doit être correcte — pas d'effet fisheye, les murs semblent plats.

---

## PHASE 4 — Mouvements et rotations (jour 4-5)
🟢 **Indépendant**

### 4.1 — Stocker l'état des touches
Plutôt que d'agir directement dans `key_press`, utilise des flags :

```c
// dans t_game ou t_player
int keys[6]; // W A S D LEFT RIGHT
```

```c
int key_press(int key, t_game *game)
{
    if (key == 65307) close_window(game);  // ESC
    if (key == 119)   game->keys[0] = 1;  // W
    if (key == 97)    game->keys[1] = 1;  // A
    if (key == 115)   game->keys[2] = 1;  // S
    if (key == 100)   game->keys[3] = 1;  // D
    if (key == 65361) game->keys[4] = 1;  // LEFT arrow
    if (key == 65363) game->keys[5] = 1;  // RIGHT arrow
    return (0);
}

int key_release(int key, t_game *game)
{
    // même logique avec = 0
}
// Ajouter : mlx_hook(game->win, 3, 1L<<1, key_release, game);
```

### 4.2 — Déplacement avant/arrière (W/S)
```c
void    move_forward_back(t_game *game, double dir)
{
    double  new_x = game->player.x + game->player.dir_x * game->player.move_speed * dir;
    double  new_y = game->player.y + game->player.dir_y * game->player.move_speed * dir;

    // Vérifier collision SÉPARÉMENT sur x et y
    if (game->map.grid[(int)game->player.y][(int)new_x] != '1')
        game->player.x = new_x;
    if (game->map.grid[(int)new_y][(int)game->player.x] != '1')
        game->player.y = new_y;
}
// Appel : move_forward_back(game, 1.0)  // W
//         move_forward_back(game, -1.0) // S
```

### 4.3 — Déplacement latéral (A/D)
```c
void    move_strafe(t_game *game, double dir)
{
    // Le vecteur perpendiculaire à dir est (-dir_y, dir_x)
    double  new_x = game->player.x + (-game->player.dir_y) * game->player.move_speed * dir;
    double  new_y = game->player.y + game->player.dir_x * game->player.move_speed * dir;

    if (game->map.grid[(int)game->player.y][(int)new_x] != '1')
        game->player.x = new_x;
    if (game->map.grid[(int)new_y][(int)game->player.x] != '1')
        game->player.y = new_y;
}
```

### 4.4 — Rotation (flèches gauche/droite)
La rotation applique une matrice 2D de rotation sur `dir` et `plane` :

```c
void    rotate_player(t_game *game, double angle)
{
    double  old_dir_x = game->player.dir_x;
    double  old_plane_x = game->player.plane_x;

    game->player.dir_x   = old_dir_x   * cos(angle) - game->player.dir_y   * sin(angle);
    game->player.dir_y   = old_dir_x   * sin(angle) + game->player.dir_y   * cos(angle);
    game->player.plane_x = old_plane_x * cos(angle) - game->player.plane_y * sin(angle);
    game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}
// Appel : rotate_player(game, -game->player.rot_speed); // LEFT
//         rotate_player(game,  game->player.rot_speed); // RIGHT
```

### 4.5 — Assembler handle_movement()
```c
void    handle_movement(t_game *game)
{
    if (game->keys[0]) move_forward_back(game, 1.0);
    if (game->keys[2]) move_forward_back(game, -1.0);
    if (game->keys[1]) move_strafe(game, -1.0);
    if (game->keys[3]) move_strafe(game, 1.0);
    if (game->keys[4]) rotate_player(game, -game->player.rot_speed);
    if (game->keys[5]) rotate_player(game,  game->player.rot_speed);
}
```

✅ **Test phase 4 :** le joueur se déplace fluidement, les collisions empêchent de traverser les murs, la rotation tourne bien sans déformer l'image.

---

## PHASE 5 — Textures (jour 5-7)
🔴 **Tu as besoin des textures chargées par ton mate**

> **Point de synchronisation :** ton mate doit te fournir `game->textures[4]` correctement remplis (img_ptr, addr, bpp, line_len, width, height) avant que tu puisses faire cette phase.
> En attendant, tu peux utiliser des couleurs unies par direction (Nord=rouge, Sud=vert, Est=bleu, Ouest=jaune).

### 5.1 — Déterminer quelle texture utiliser
```c
// Après la boucle DDA, selon side et step :
int tex_id;
if (side == 0 && step_x > 0) tex_id = 2; // EA (Est)
if (side == 0 && step_x < 0) tex_id = 0; // NO (Nord... selon ta convention)
if (side == 1 && step_y > 0) tex_id = 1; // SO (Sud)
if (side == 1 && step_y < 0) tex_id = 3; // WE (Ouest)
// ⚠️ À vérifier avec ton mate selon son ordre de chargement des textures
```

### 5.2 — Calculer la colonne X dans la texture
```c
double wall_x; // où exactement le rayon frappe le mur (0.0 à 1.0)
if (side == 0) wall_x = game->player.y + perp_wall_dist * ray_dir_y;
else           wall_x = game->player.x + perp_wall_dist * ray_dir_x;
wall_x -= floor(wall_x);

// Colonne de pixel dans la texture
int tex_x = (int)(wall_x * game->textures[tex_id].width);
// Correction miroir selon le sens du rayon
if (side == 0 && ray_dir_x > 0) tex_x = game->textures[tex_id].width - tex_x - 1;
if (side == 1 && ray_dir_y < 0) tex_x = game->textures[tex_id].width - tex_x - 1;
```

### 5.3 — Dessiner la colonne texturée
```c
double step_tex = 1.0 * game->textures[tex_id].height / line_height;
double tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step_tex;

for (int y = draw_start; y < draw_end; y++)
{
    int tex_y = (int)tex_pos & (game->textures[tex_id].height - 1);
    tex_pos += step_tex;

    // Lire la couleur depuis le buffer de la texture
    char *tex_addr = game->textures[tex_id].addr
        + (tex_y * game->textures[tex_id].line_len
        + tex_x * (game->textures[tex_id].bpp / 8));
    int color = *(unsigned int *)tex_addr;

    // Assombrir les murs de côté (effet de profondeur)
    if (side == 1) color = (color >> 1) & 0x7F7F7F;

    put_pixel(&game->screen, x, y, color);
}
```

✅ **Test phase 5 :** les murs ont des textures qui s'étirent correctement selon la distance, les 4 directions ont des textures différentes.

---

## PHASE 6 — Intégration du parsing (jour 6-8)
🔴 **Dépend de ton mate**

> **Point de synchronisation :** ton mate te livre la fonction `init_game_from_file(t_game *game, char *path)` qui remplit :
> - `game->map` (grille parsée)
> - `game->textures[4]` (images chargées)
> - `game->floor_color` et `game->ceil_color`
> - `game->player` position et orientation initiales

### 6.1 — Remplacer ta map hardcodée
```c
// main.c
int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        return (ft_error("Usage: ./cub3D map.cub"));
    ft_memset(&game, 0, sizeof(t_game));
    // Remplacer init_test_map() par :
    if (init_game_from_file(&game, argv[1]))
        return (1);
    init_mlx(&game);
    mlx_loop(game.mlx);
    return (0);
}
```

### 6.2 — Vérifier la compatibilité des structs
- Confirme avec ton mate que les champs de `t_map`, `t_player`, `t_img` sont exactement ceux définis en Phase 0.3
- Teste avec toutes les maps fournies dans le sujet

✅ **Test phase 6 :** le programme accepte un vrai fichier `.cub`, parse et affiche correctement.

---

## PHASE 7 — Nettoyage et conformité au sujet (jour 8-9)
🟡 **En binôme**

### 7.1 — Checklist obligatoire
- [ ] `ESC` ferme proprement (free tout, exit(0))
- [ ] Croix rouge ferme proprement
- [ ] W/A/S/D bougent
- [ ] Flèches gauche/droite tournent
- [ ] 4 textures de mur différentes selon direction
- [ ] Plafond et sol en couleur unie (RGB depuis .cub)
- [ ] Erreur retourne `"Error\n"` + message explicite
- [ ] Map fermée par des murs (validé par ton mate côté parsing)
- [ ] Gestion si mlx_init échoue, malloc échoue, etc.
- [ ] Pas de leak mémoire (valgrind)
- [ ] Pas de crash sur maps valides et invalides

### 7.2 — Norminette
```bash
norminette srcs/ includes/
```

### 7.3 — Tests avec des maps limites
- Map minimale (3x3)
- Map très grande
- Joueur dans un coin
- Longs couloirs
- Pièces ouvertes

---

## PHASE 8 — README (dernier jour)
🟡 **En binôme**

Le README est **obligatoire** selon le sujet. Il doit contenir :

1. Première ligne en italique : `*This project has been created as part of the 42 curriculum by login1, login2.*`
2. Section **Description** : présentation du projet, objectif, overview
3. Section **Instructions** : compilation, installation, exécution
4. Section **Resources** : références (lodev raycasting, wiki raycasting) + comment vous avez utilisé l'IA

---

## Résumé des points de synchro avec ton mate

| Phase | Ce dont tu as besoin | Quand |
|-------|---------------------|-------|
| Phase 0.3 | Valider les structs communes ensemble | Jour 1 — AVANT tout code |
| Phase 5 | `game->textures[4]` chargés correctement | Dès que son parsing est prêt |
| Phase 6 | `init_game_from_file()` fonctionnelle | Quand parsing + textures OK |
| Phase 8 | Rédiger le README ensemble | Fin de projet |

---

## Ressources clés

- **Lodev raycasting tutorial** (la référence) : https://lodev.org/cgtutor/raycasting.html
- **MinilibX docs** : https://harm-smits.github.io/42docs/libs/minilibx
- **Wiki raycasting** : https://en.wikipedia.org/wiki/Ray_casting
