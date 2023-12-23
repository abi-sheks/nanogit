#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

void fs_mkdir(const std::string dir)
{
    if (fs::status(dir).type() == fs::file_type::not_found)
    {
        fs::create_directory(dir);
    }
    else
    {
        throw std::runtime_error("already exists");
    }
}

void fs_rm(const std::string filename)
{
    if (!fs::remove(filename))
    {
        throw std::runtime_error("Could not delete");
    }
}

std::string read_string_from_file(const std::string filename)
{
    std::ifstream fp;
    fp.open(filename);
    std::string result;
    std::getline(fp, result);
    fp.close();
    return result;
}
void write_string_to_file(const std::string filename, const std::string str)
{
    std::ofstream fp;
    fp.open(filename);
    fp << str;
    fp.close();
}

bool is_exists(const std::string filename)
{
    // checks whether file exists and is a file
    auto file_status = fs::status(filename).type();
    return file_status != fs::file_type::not_found;
}