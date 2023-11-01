/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeft_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumamur <yumamur@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:18:43 by yumamur           #+#    #+#             */
/*   Updated: 2023/11/01 13:18:43 by yumamur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEFT_BONUS_H
# define TYPEFT_BONUS_H

# include <stdlib.h>

typedef signed char					t_int8;
typedef signed short				t_int16;
typedef signed int					t_int32;
typedef signed long int				t_int64;

typedef unsigned char				t_uint8;
typedef unsigned short				t_uint16;
typedef unsigned int				t_uint32;
typedef unsigned long int			t_uint64;

typedef unsigned char				t_uchar;
typedef unsigned short				t_ushort;
typedef unsigned int				t_uint;
typedef unsigned long				t_ulong;
typedef unsigned long long			t_ullong;

typedef const void					t_c_void;
typedef const char					t_c_char;
typedef const short					t_c_short;
typedef const int					t_c_int;
typedef const long					t_c_long;
typedef const long long				t_c_llong;

typedef const unsigned char			t_c_uchar;
typedef const unsigned short		t_c_ushort;
typedef const unsigned int			t_c_uint;
typedef const unsigned long			t_c_ulong;
typedef const unsigned long long	t_c_ullong;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;
#endif /* TYPEFT_H */