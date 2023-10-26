#include "philo.h"

int		print_status(t_philo *philo, enum e_state status);

int	enjoy_the_meals(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork))
		return (put_error(PERR_MLOCK));
	if (print_status(philo, FORK))
		return (-1);
	if (pthread_mutex_lock(philo->right_fork))
		return (put_error(PERR_MLOCK));
	if (print_status(philo, FORK))
		return (-1);
	if (pthread_mutex_lock(&philo->table->monitor))
		return (put_error(PERR_MLOCK));
	++philo->ct_of_eat;
	if (print_status(philo, EATING))
		return (-1);
	philo->last_eat = philo_timer(CURR);
	if (pthread_mutex_unlock(&philo->table->monitor))
		return (put_error(PERR_MUNLOCK));
	if (precise_sleep(philo->table->time_to_eat))
		return (put_error(PERR_TIMER));
	if (pthread_mutex_unlock(philo->left_fork))
		return (put_error(PERR_MUNLOCK));
	if (pthread_mutex_unlock(philo->right_fork))
		return (put_error(PERR_MUNLOCK));
	return (0);
}

void	*philo_routine(t_philo *philo)
{
	while (!philo->table->flag_death && !philo->table->flag_done)
	{
		if (enjoy_the_meals(philo))
			return (NULL);
		if (print_status(philo, SLEEPING))
			return (NULL);
		precise_sleep(philo->table->time_to_sleep);
		if (print_status(philo, THINKING))
			return (NULL);
		precise_sleep(500);
	}
	return (NULL);
}
