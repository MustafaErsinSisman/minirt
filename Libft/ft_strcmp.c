
int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str2 == '0')
		str2++;
	while (*str1 == '0')
		str1++;
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
