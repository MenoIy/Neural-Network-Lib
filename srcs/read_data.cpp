/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:30:30 by kdaou             #+#    #+#             */
/*   Updated: 2020/01/07 19:42:03 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"
#include <pthread.h>
#include <sstream>
#include <fstream>
#include "matrix.hpp"
#include <string>


struct thread_data 
{
	const char	*path;
	struct Data	**data;
};

static void	save_data(string line, struct Data **data)
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
	for (int  j = 0; j < label.row; j++)
		label.tab[j][0] = 0.001;
	label.tab[vd[0]][0] = 0.999;
	for (int i = 1; i < 785; i++)
		inputs.tab[i - 1][0] = vd[i];
	push_data(data, label, inputs);
}

static void	*read_data(void *data)
{
	struct	thread_data *td;
	td = (struct thread_data *)data;
	ifstream	stm(td->path);

	string	line="";
	getline(stm, line);
	while(getline(stm, line)){
		save_data(line, td->data);
	}
	stm.close();
	pthread_exit(NULL);
}

void	get_data(struct Data **train_data, struct Data **test_data, const char *train_data_path, const char *test_data_path)
{
	pthread_t threads[2];
	struct thread_data	td[2];

	td[0].path = train_data_path;
	td[0].data = train_data;
	td[1].path = test_data_path;
	td[1].data = test_data;

	if (pthread_create(&threads[0], NULL, read_data, (void *)&td[0]))
	{
		cout << "Error:unable to create thread, 1 " << endl;
		exit(-1);
	}
	if (pthread_create(&threads[1], NULL, read_data, (void *)&td[1]))
	{
		cout << "Error:unable to create thread, 2 " << endl;
		exit(-1);
	}
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
}
