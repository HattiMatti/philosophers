/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiitone <msiitone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:36:15 by msiitone          #+#    #+#             */
/*   Updated: 2024/07/22 17:36:17 by msiitone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	think(t_philo *philo)
{
	print_message("is thinking", philo);
}

void	take_forks(t_philo *philo)
{
	int		left_fork;
	int		right_fork;
	t_table	*table;

	table = philo->table;
	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&table->forks[left_fork]);
		print_message("has taken a fork", philo);
		pthread_mutex_lock(&table->forks[right_fork]);
		print_message("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(&table->forks[right_fork]);
		print_message("has taken a fork", philo);
		if (table->died)
			return ;
		pthread_mutex_lock(&table->forks[left_fork]);
		print_message("has taken a fork", philo);
	}
}

void	eat(t_philo *philo)
{
	t_table	*table;

	printf("testest");
	table = philo->table;
	print_message("is eating", philo);
	philo->last_meal = get_time();
	if (philo->table->nbr_of_meals != -1)
		philo->meals_eaten++;
	usleep(table->time_to_eat * 1000);
	pthread_mutex_unlock(&table->forks[(philo->left_fork + 1)
		% table->nbr_of_philos]);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	print_message("has put down forks", philo);
}

void	philo_sleep(t_philo *philo)
{
	print_message("is sleeping", philo);
	usleep(philo->table->time_to_sleep * 1000);
}
