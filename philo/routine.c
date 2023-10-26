#include "philo.h"

int		print_status(t_philo *philo, enum e_state status);

int	enjoy_the_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK);
	philo->last_eat = philo_timer();
	print_status(philo, EATING);
	precise_sleep(philo->table, philo->table->time_to_eat);
	++(philo->ct_of_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*philo_routine(t_philo *philo)
{
	while (!philo->table->flag_death && !philo->table->flag_done)
	{
		enjoy_the_meals(philo);
		print_status(philo, SLEEPING);
		precise_sleep(philo->table, philo->table->time_to_sleep);
		print_status(philo, THINKING);
	}
	return (NULL);
}
