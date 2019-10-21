// Copyright 2019 Volkgrig

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <boost/filesystem.hpp>
#include "string"
#include "vector"
#include "iostream"
using boost::filesystem::path;
using boost::filesystem::directory_iterator;
using boost::filesystem::directory_entry;

struct File {
    std::string broker;
    std::string account;
    std::string date;
    size_t num;
    File(std::string, std::string);
};

bool checkName(std::string);

bool checkDate(int, int, int);

void processDirectory(const path&, std::vector<File>&);

int mainVirtual(int, char* argv[]);

std::ostream& operator<<(std::ostream&, const File&);

#endif // INCLUDE_HEADER_HPP_
