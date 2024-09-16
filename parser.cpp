#include "parser.h"
#include "const.h"

#include <sstream>
#include <iostream>
#include <cmath>

Parser::Parser()
{

}

void Parser::parsingFileBuffer(const std::vector<std::string>&& file_buffer, const std::string&& file_name)
{
	filename = file_name;

	parsingFileHeader(file_buffer[0]);

	for (size_t i = 1; i < file_buffer.size(); ++i) {
		std::istringstream input {file_buffer[i]};
		std::vector<std::string> result;

		while (!input.eof()) {
				std::string substring;
				input >> substring;
				result.push_back(substring);
		}

		for (size_t j = 0; j < result.size(); ++j) {
			if (file_name == c_inklin_absolute) {
				data_file_absolute[hdr_index[j]].push_back(std::stod(result[j]));
			}
			else if (file_name == c_inklin_azim) {
				data_file_azim[hdr_index[j]].push_back(std::stod(result[j]));
			}
			else if (file_name == c_inklin_delta) {
				data_file_delta[hdr_index[j]].push_back(std::stod(result[j]));
			}
		}
	}

	if (filename == c_inklin_absolute) {
		workWithFileAbsolute();
	}
	else if (filename == c_inklin_azim) {
		workWithFileAzim();
	}
	else if (filename == c_inklin_delta) {
		workWithFileDelta();
	}
}

std::string Parser::getFilename()
{
	return filename;
}

std::vector<double> Parser::getCoordX()
{
	return coord_x;
}

std::vector<double> Parser::getCoordY()
{
	return coord_y;
}

std::vector<double> Parser::getCoordZ()
{
	return coord_z;
}

void Parser::clearData()
{
	filename = "";

	if (!coord_x.empty()) coord_x.clear();
	if (!coord_y.empty()) coord_y.clear();
	if (!coord_z.empty()) coord_z.clear();

	if (!hdr_index.empty()) hdr_index.clear();
	if (!data_file_absolute.empty()) data_file_absolute.clear();
	if (!data_file_azim.empty()) data_file_azim.clear();
	if (!data_file_delta.empty()) data_file_delta.clear();

}

void Parser::parsingFileHeader(const std::string& hdr)
{
	std::string arg {""};
	unsigned int index {0};

	for (size_t i = 0; i < hdr.length(); ++i) {
		if (std::isalnum(hdr[i]) || std::isdigit(hdr[i])) {
			arg += hdr[i];

			if (i == hdr.length() - 1) hdr_index[index] = arg;

		}
		else {
			hdr_index[index] = arg;
			arg = "";
			index++;
		}
	}
}

void Parser::workWithFileAbsolute()
{
	coord_x = data_file_absolute[c_X];

	coord_y = data_file_absolute[c_Y];

	coord_z = calcTVD();
}

void Parser::workWithFileAzim()
{
	// расчет для файла азимута
}

void Parser::workWithFileDelta()
{
	// расчет для файла дельты
}

std::vector<double> Parser::calcTVD()
{
	size_t size = std::min(std::min(data_file_absolute[c_X].size(), data_file_absolute[c_Y].size()), data_file_absolute[c_MD].size());
	std::vector<double> tvd;
	tvd.reserve(size);

	for (size_t i = 1; i < size; ++i) {
		auto a {pow((data_file_absolute[c_X].at(i) - data_file_absolute[c_X].at(i-1)), 2)};
		auto b {pow((data_file_absolute[c_Y].at(i) - data_file_absolute[c_Y].at(i-1)), 2)};
		auto c {pow((data_file_absolute[c_MD].at(i) - data_file_absolute[c_MD].at(i-1)), 2)};

		tvd.push_back(sqrt(c - (a + b)));
	}

	return tvd;
}
