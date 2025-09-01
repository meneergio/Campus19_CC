/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:10:05 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/13 13:31:34 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	total;

	if (count && size && count > SIZE_MAX / size)
	{
		return (NULL);
	}
	total = count * size;
	p = malloc (total);
	if (!p)
		return (NULL);
	ft_bzero(p, total);
	return (p);
}
/*
#include <stdio.h>

int main(void)
{
    // Test 1: Alloceren van een array van 5 integers,
	// alle elementen moeten op 0 staan
    int *arr1 = (int *)ft_calloc(5, sizeof(int));
    if (arr1)
    {
        printf("Test 1: Array van 5 integers, waarden: ");
        for (int i = 0; i < 5; i++)
            printf("%d ", arr1[i]);
        printf("\n");
        free(arr1);  // Vergeet niet het geheugen vrij te geven
    }
    else
    {
        printf("Test 1: Geheugenallocatie mislukt.\n");
    }

    // Test 2: Alloceren van een array van 0 elementen 
	// (geen geheugen moet worden toegewezen)
    int *arr2 = (int *)ft_calloc(0, sizeof(int));
    if (arr2 == NULL)
    {
        printf("Test 2: Geen geheugen toegewezen voor array van 0 elementen, ");
		printf("zoals verwacht.\n");
    }
    else
    {
        printf("Test 2: Geheugenallocated voor 0 elementen, ");
		printf("wat niet zou moeten gebeuren.\n");
        free(arr2);
    }

    // Test 3: Alloceren van een array van 3 doubles
    double *arr3 = (double *)ft_calloc(3, sizeof(double));
    if (arr3)
    {
        printf("Test 3: Array van 3 doubles, waarden: ");
        for (int i = 0; i < 3; i++)
            printf("%f ", arr3[i]);
        printf("\n");
        free(arr3);
    }
    else
    {
        printf("Test 3: Geheugenallocatie mislukt.\n");
    }

    return 0;
}
// verwachte return 
// Test 1: Array van 5 integers, waarden: 0 0 0 0 0 
// Test 2: Geheugenallocated voor 0 elementen, wat niet zou moeten gebeuren.
// Test 3: Array van 3 doubles, waarden: 0.000000 0.000000 0.000000 
*/
