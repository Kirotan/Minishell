#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		new = tmp->next;
		del(tmp->content);
		free(tmp);
		tmp = new;
	}
	*lst = NULL;
}
