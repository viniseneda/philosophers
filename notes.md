philosopher (data)
{
    while (times_to_eat > 0)
    {
		start time
		print is thinking
		while (try to eat)
		{
			verify if dead
			{
				print dead
				return
			}
		}
		print is sleeping
		sleep
    }
}

int	get_right(data)
{
	
}

print_message(char *, mutex *)
{
	lock mutex
	print
	unlock mutex
}

try to eat (data)
{
	if fork right and fork left
	{
		lock right
		set right to 0
		lock left
		set right to 0
		print is eating
		usleep(time to eat)
		set right to 1
		unlock right
		set left to 1
		unlock left
	}
}