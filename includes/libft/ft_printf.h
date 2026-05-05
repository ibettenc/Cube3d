/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:53:38 by ibettenc          #+#    #+#             */
/*   Updated: 2025/04/30 13:12:06 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h> // va_list, va_...
#include <stdint.h> // uintptr_t
#include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_puthexa(unsigned int j, char c);
int	ft_putptr(void *p);
int	ft_putunsigned(unsigned int n);
