/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 16:04:44 by kdaou             #+#    #+#             */
/*   Updated: 2020/01/10 09:30:43 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "list.hpp"
#include "network.hpp"

void	get_data(struct Data **train_data, struct Data **test_data, const char *train_data_path, const char *test_data_path);



void	func(struct Data **train_data, struct Data **test_data)
{
	for (int i = 0; i < 100; i++)
	{
		int count = 0;
		Matrix		label(2,1);
		Matrix		inputs(9, 1);
		inputs.randomize();
		for (int j = 0; j < 9; j++)
		{
			if (inputs.tab[j][0] <= 0)
				count++;
		}
		label.tab[0][0] = 0.01;
		label.tab[0][0] = 0.01;

		if (count > 4)
			label.tab[0][0] = 0.99;
		else
			label.tab[1][0] = 0.99;

		push_data(train_data, label, inputs);
	}
	for (int i = 0; i < 10; i++)
	{
		int count = 0;
		Matrix		label(2,1);
		Matrix		inputs(9, 1);
		inputs.randomize();
		for (int j = 0; j < 9; j++)
		{
			if (inputs.tab[j][0] <= 0)
				count++;
		}

		label.tab[0][0] = 0.01;
		label.tab[0][0] = 0.01;
		if (count > 4)
			label.tab[0][0] = 0.99;
		else
			label.tab[1][0] = 0.99;
		push_data(test_data, label, inputs);
	}
}

int main()
{
	int	hidden[] = {5, 5};
	Network	net(784,2, hidden, 10);
	struct Data* train_data =  NULL;
	struct Data* test_data = NULL;

	get_data(&train_data, &test_data, "data/train.csv", "data/test.csv");
	//func(&train_data, &test_data);
	cout << "start training \n";
	net.sgd_v1(train_data, 50, 1025, 0.1, test_data);
	del_data(&test_data);
	del_data(&train_data);
	return (0);
}

