#include "minishell.h"

int main(void)
{
	char	**split;
	char	*to_split;
	int		i;

	to_split = ft_strdup("'hi hi' \"test\"      'haha haha' haha");
	split = mini_split(to_split, ' ');
	i = 0;
	while (split[i])
	{
		ft_printf("[%s]", split[i]);
		i++;
	}
	ft_printf("\n");
}
