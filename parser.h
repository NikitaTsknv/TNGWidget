#ifndef PARSER_H
#define PARSER_H

#include<vector>
#include<unordered_map>
#include<string>

class Parser
{
public:
	Parser();

	void parsingFileBuffer(const std::vector<std::string>&& file_buffer, const std::string &&file_name);
	std::string getFilename();
	std::vector<double> getCoordX();
	std::vector<double> getCoordY();
	std::vector<double> getCoordZ();
	void clearData();

private:
	std::string filename {""};
	std::unordered_map<size_t, std::string> hdr_index;
	std::unordered_map<std::string, std::vector<double>> data_file_absolute;
	std::unordered_map<std::string, std::vector<double>> data_file_azim;
	std::unordered_map<std::string, std::vector<double>> data_file_delta;

	std::vector<double> coord_x;
	std::vector<double> coord_y;
	std::vector<double> coord_z;

	void parsingFileHeader(const std::string& hdr);

	void workWithFileAbsolute();
	void workWithFileAzim();
	void workWithFileDelta();

	std::vector<double> calcTVD();
};

#endif // PARSER_H
