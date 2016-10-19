#include "Parametry.h"

using namespace std;

bool parse_parameters(int argc, char**argv, string& input_file_name, string& input_file_name_2, string& output_file_name)
{
	input_file_name = "";
	input_file_name_2 = "";
	output_file_name = "";
	const string input_switch = "-t";
	const string input_switch_2 = "-b";
	const string output_switch = "-o";

	for (int i = 1; i < argc - 1; ++i)
	{
		if (argv[i] == input_switch)
		{
			input_file_name = argv[++i];
		}
		else if (argv[i] == output_switch)
		{
			output_file_name = argv[++i];
		}
		else if (argv[i] == input_switch_2)
		{
			input_file_name_2 = argv[++i];
		}
	}

	if (input_file_name == "" || input_file_name_2 == "" || output_file_name == "")
	{
		return false;
	}
	return true;
}