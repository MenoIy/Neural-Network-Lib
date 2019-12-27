/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 16:04:44 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/27 23:29:42 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "list.hpp"
#include "network.hpp"




/*void	guess(Network net, string line)
{
	Matrix		label(10,1);
	Matrix		inputs(784, 1);
	std::vector< double > vd;

	int pos = 0;
	double	d = 0.0;

	while (pos < line.size())
	{
		if ((pos = line.find_first_of (',',pos)) != std::string::npos)
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
	Matrixi
}*/


void	get_data_and_train(Network net, string line)
{
	Matrix		label(10,1);
	Matrix		inputs(784, 1);
	std::vector< double > vd;

	int pos = 0;
	double	d = 0.0;

	while (pos < line.size())
	{
		if ((pos = line.find_first_of (',',pos)) != std::string::npos)
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
	net.train(inputs, label, 0.1);
}

int main()
{
	ifstream	file("train.csv");
	string		line;
	Network		net(784, 30, 10);
	struct Data* data =  NULL;

	Matrix c(2, 2);
	getline(file, line);
	int i = 0;
	while (getline(file, line))
	{
		get_data_and_train(net, line);
		data_push(&data,c, c);
		i++;
		if (i < 20)
			break;
	}
	file.close();

	struct Data* tmp;
	tmp = data;
	while (tmp != NULL)
	{
		tmp->label.print();
		tmp = tmp->next;
	}
	//guess(net, file);
}







/*
   int main()
   {
   Network	net(5, 8, 2);
   net.print();
   Matrix inp(5, 1);
   inp.randomize();
   Matrix target(2, 1);
   target.randomize();
   net.train(inp, target, 0.1);
   net.print();
   return (0);
   }*/
