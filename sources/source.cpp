// Copyright 2019 Volkgrig

#include "../include/header.hpp"


File::File(std::string pam, std::string fin): 
    broker(pam), 
    account(fin.substr(8, 8)), 
    num(1), 
    date(fin.substr(17, 8)) {
}


bool checkName(std::string filename) {
    if (filename.length() != 29) {
        return true;
    }
    if (filename.substr(0, 8) != "balance_") {
        return true;
    }
    for (size_t i = 8; i < 16; i++) {
        if (filename[i] < '0' || filename[i] > '9') {
            return true;
        }
    }
    if (filename[16] != '_') {
        return true;
    }
    for (size_t i = 17; i < 25; i++) {
        if (filename[i] < '0' || filename[i] > '9') {
            return true;
        }
    }
    if (filename[25] != '.') {
        return true;
    }
    return false;
}


bool checkDate(int year, int month, int day) {
    if (year < 1970 || year > 2019) { return true; }
    if (month < 0 || month > 12) { return true; }
    if (day < 0) { return true; }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) { return true; }
    } else if (month == 2) {
        if (year % 4 == 0) {
            if (day > 29) { return true; }
        } else {
            if (day > 28) { return true; }
        }
    } else {
        if (day > 31) { return true; }
    }
    return false;
}


void processDirectory(const path& p, std::vector<File>& pam) {
    if (!exists(p)) {
        std::cout << "Not exist: " << p << "\n";
        exit(-1);
    }
    for (auto& x : directory_iterator{ p }) {
        if (boost::filesystem::is_directory(x.path())) {
            processDirectory(x.path(), pam);
        }
        if (boost::filesystem::is_regular_file(x.path())) {
            std::string filename = x.path().filename().string();
            if (checkName(filename)) { continue; }
            int year = 1000 * (filename[17] - 48) + 10 * (filename[18] - 48) +
                10 * (filename[19] - 48) + filename[20] - 48;
            int month = 10 * (filename[21] - 48) + filename[22] - 48;
            int day = 10 * (filename[23] - 48) + filename[24] - 48;
            if (checkDate(year, month, year)) { continue; }
            std::cout << p.filename().string() << " " << filename << std::endl;
            File newF(p.filename().string(), filename);
            bool fl = false;
            for (auto& cur : pam) {
                if (cur.broker == newF.broker) {
                    if (cur.account == newF.account) {
                        fl = true;
                        cur.date = cur.date > newF.date
                            ? cur.date : newF.date;
                        cur.num++;
                    }
                }
            }
            if (!fl) {
                pam.push_back(newF);
            }
        }
    }
}


int mainVirtual(int argc, char* argv[]) {
    const boost::filesystem::path p(boost::filesystem::current_path());
    if (argc == 2) {
        const boost::filesystem::path p(argv[1]);
    }
    std::vector<File> files;
    processDirectory(p, files);
    for (auto cur : files) {
        std::cout << "\n" << cur; 
   }
    return 0;
}


std::ostream& operator<<(std::ostream& out, const File& file) {
    out << "broker:" << file.broker 
        << " account:" << file.account
        << " files:" << file.num 
        << " lastdate:" << file.date;
    return out;
}
