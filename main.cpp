#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

#ifdef _WIN32
#include <intrin.h>
#endif

struct command_line_args
{
    int alpha;
    double start_log_time;
    double log_time_increment;
    double end_log_time;
    std::string input_file_name;
    std::string output_file_name;
};

std::vector<uint32_t> compute_bin_numbers(const std::vector<uint32_t> &data, double bin_time)
{
    std::vector<uint32_t> bin_numbers(data.size());
    int i;
    for (i = 0; i < data.size(); i++)
    {
        bin_numbers[i] = (int)floor(data[i] / bin_time);
    }

    return bin_numbers;
}

uint64_t compute_shifted_sum(std::vector<uint32_t> &data, int alpha)
{
    uint64_t shift_sum = 0;

    int i = 0;
    while (i < data.size())
    {
        int bin_count = 0;
        int shift_count = 0;
        int boundary = -1;

        int j;
        for (j = i; data[j] <= data[i] + alpha && j < data.size(); j++)
        {
            if (data[j] == data[i])
            {
                bin_count++;
            }
            else
            {
                if (boundary < 0)
                {
                    boundary = j;
                }

                if (data[j] == data[i] + alpha)
                {
                    shift_count++;
                }
            }
        }

        shift_sum += bin_count * shift_count;
        i = boundary >= 0 ? boundary : j;
    }

    return shift_sum;
}

int parse_command_line_int(std::string val, std::string param_name)
{
    try
    {
        int v = std::stoi(val);
        return v;
    }
    catch (std::invalid_argument &ex)
    {
        std::cout << "Invalid value for parameter " << param_name << ". Value must be a floating-point number" << std::endl;
        exit(1);
    }
}

double parse_command_line_double(std::string val, std::string param_name)
{
    try
    {
        double v = std::stod(val);
        return v;
    }
    catch (std::invalid_argument &ex)
    {
        std::cout << "Invalid value for parameter " << param_name << ". Value must be an integer" << std::endl;
        exit(1);
    }
}

command_line_args parse_command_line_args(int argc, char *argv[])
{
    command_line_args args;
    args.alpha = 5;
    args.start_log_time = -6.5;
    args.log_time_increment = 0.1;
    args.end_log_time = 1;

    for (int i = 1; i < argc - 1; i += 2)
    {
        std::string key = argv[i];
        std::string val = argv[i + 1];

        if (key == "--alpha" || key == "-a")
        {
            args.alpha = parse_command_line_int(val, key);
        }
        else if (key == "--start-log-time" || key == "-s")
        {
            args.start_log_time = parse_command_line_double(val, key);
        }
        else if (key == "--inc-log-time" || key == "-i")
        {
            args.log_time_increment = parse_command_line_double(val, key);
        }
        else if (key == "--end-log-time" || key == "-e")
        {
            args.end_log_time = parse_command_line_double(val, key);
        }
        else if (key == "--input-file-name" || key == "-if")
        {
            args.input_file_name = val;
        }
        else if (key == "--output-file-name" || key == "-of")
        {
            args.output_file_name = val;
        }
        else
        {
            std::cout << "Invalid argument " << val << ". Valid arguments are\n"
                      << "\t --input-file-name (-if) (required): the name of the input file containing binary data"
                      << "\t --output-file-name (-of) (required): the name of the file where output data should be written"
                      << "\t --alpha (-a) (optional, default value 5): the number of bins by which to shift\n"
                      << "\t --start-log-time (-s) (optional, default value -6.5): the base-10 log of the first bin size\n"
                      << "\t --inc-log-time (-i) (optional, default value 0.1): the base-10 log of the bin size increment\n"
                      << "\t --end-log-time (-e) (optional, default value 1): the base-10 log of the last bin size" << std::endl;
            exit(1);
        }
    }

    if (args.input_file_name.size() == 0 || args.output_file_name.size() == 0)
    {
        std::cout << "Input file name (--input-file-name, -if) and output file name (--output-file-name, -of) must be provided as arguments" << std::endl;
        exit(1);
    }

    return args;
}

double compute_data_point(const std::vector<uint32_t> &raw_data, int alpha, double bin_time, double bin_exp)
{
    std::vector<uint32_t> bin_numbers = compute_bin_numbers(raw_data, bin_time);
    uint32_t max_bin = bin_numbers[bin_numbers.size() - 1];
    uint64_t shift_sum = compute_shifted_sum(bin_numbers, alpha);

    double shift_avg = ((double)shift_sum / (max_bin - alpha));
    double avg_squared = pow((double)bin_numbers.size() / max_bin, 2);
    return shift_avg / avg_squared - 1;
}

int main(int argc, char *argv[])
{
    command_line_args args = parse_command_line_args(argc, argv);

    std::vector<uint32_t> data;
    std::ifstream input_file(args.input_file_name);

    while (!input_file.eof())
    {
        uint32_t val = 0;
        input_file.read(reinterpret_cast<char *>(&val), sizeof(val));
#ifdef _WIN32
        data.push_back(_byteswap_ulong(val));
#else
        data.push_back(__builtin_bswap32(val));
#endif
    }

    input_file.close();

    data.erase(data.begin());
    double clock_frequency = data[0];
    data.erase(data.begin());
    data.erase(data.end() - 1);

    std::ofstream output_file(args.output_file_name);
    for (double bin_size_exp = args.start_log_time; bin_size_exp <= args.end_log_time; bin_size_exp += args.log_time_increment)
    {
        double bin_time = pow(10, bin_size_exp) * clock_frequency / args.alpha;
        double value = compute_data_point(data, args.alpha, bin_time, bin_size_exp);
        std::string row = std::to_string(bin_size_exp) + "," + std::to_string(value) + "\n";
        output_file.write(row.c_str(), row.size());
    }

    output_file.close();
    return 0;
}
