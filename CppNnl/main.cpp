/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 16:04:44 by kdaou             #+#    #+#             */
/*   Updated: 2020/01/01 19:31:34 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "list.hpp"
#include "network.hpp"


void	get_data(string line, struct Data **data)
{
	Matrix		label(10,1);
	Matrix		inputs(784, 1);
	std::vector< double > vd;

	int pos = 0;
	double	d = 0.0;
	while (pos < line.size())
	{
		if ((pos = line.find_first_of (',', pos)) != std::string::npos)
			line[pos] = ' ';
	}
	std::stringstream ss(line);
	while (ss >> d)
	{
		vd.push_back(d);
		if (ss.peek() == ',')
			ss.ignore();
	}
	label.tab[vd[0]][0] = 1.0;
	for (int i = 1; i < 785; i++)
		inputs.tab[i - 1][0] = vd[i];
	push_data(data, label, inputs);
}


static void	read_data(ifstream& stm, struct Data** data)
{
	string	line="";

	getline(stm, line);
	while (getline(stm, line) )
		get_data(line, data);
}

int main()
{
	ifstream	train("data/train.csv");
	ifstream	test("data/test.csv");
	int	hidden[] = {30};
	Network	net(784, 1, hidden, 10);
	struct Data* train_data =  NULL;
	struct Data* test_data = NULL;

/*	cout << "Reading data for train\n";
	read_data(train, &train_data);	*/
	cout << "Reading data for test\n";
	read_data(test, &test_data);
	net.sgd(test_data, 160, 1000, 0.1, test_data);
	del_data(&test_data);
	del_data(&train_data);
	test.close();
	train.close();
	return (0);
}

