/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:32:06 by motero            #+#    #+#             */
/*   Updated: 2022/05/16 18:23:11 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_ptr;

	new_ptr = (char *) malloc ((ft_strlen(s) * sizeof(char)) + 1);
	if (!new_ptr)
		return (NULL);
	ft_memmove(new_ptr, s, ft_strlen(s) + 1);
	return (new_ptr);
}

/*#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    const char * original = "The original string.";

    // On duplique la chaîne de caractères initiale.
    char * copy = ft_strdup( original );
    
    // On passe chaque lettre en majuscule.
    char * ptr = copy;
    while( *ptr != '\0' ) {
        *ptr = toupper( *ptr );
        ptr++;
    }

    // On affiche la chaîne finale
    printf( "%s\n", copy );

    // Sans oublier de libérer l'espace mémoire au final.
    free( copy );

    return EXIT_SUCCESS;
}*/
