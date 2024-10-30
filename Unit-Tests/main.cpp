#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <iomanip>
#include <filesystem>
#include <string>
#include <memory>

using namespace std;


namespace fs = std::filesystem;

std::unique_ptr<std::string[]> getFileNames(const std::string& folderPath, int& fileCount)
{
    fileCount = 0;
    for (const auto& entry : fs::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
            fileCount++;
    }

    auto fileNames = std::make_unique<std::string[]>(fileCount);
    int index = 0;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            fileNames[index] = entry.path().filename().string();
            index++;
        }
    }

    return (fileNames);
}

int main(void)
{
    int validFileCount = 0;
    int notValidFileCount = 0;
    std::string validFolderPath = "./Unit-Tests/files/Valid";
    std::string notValidFolderPath = "./Unit-Tests/files/Not-Valid";

    auto valid = getFileNames(validFolderPath, validFileCount);
    auto notValid = getFileNames(notValidFolderPath, notValidFileCount);
    pid_t c_pid;
    string str;
    const char *ptr;
    int i = 0;
    int status;
    int ret = 0;
    int pass = 0;

    while (i < validFileCount)
    {
        c_pid = fork();

        if (c_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (c_pid == 0)
        {
            int fd = open("Unit-Tests/cub3D_output", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
            if (fd < 0)
            {
                perror("Failed to open cub3D_output");
                exit(EXIT_FAILURE);
            }

            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);

            str = "./cub3D Unit-Tests/files/Valid/";
            str += valid[i];
            ptr = str.c_str();
            cerr << ptr << endl;
            ret = system(ptr);
            exit(ret != 0 ? EXIT_FAILURE : EXIT_SUCCESS);
        }
        waitpid(c_pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS && ++pass)
            cout << left << setw(50) << setfill('-') << valid[i] << "------> test case \033[0;32mpass\033[0m" << endl;
        else
            cout << left << setw(50) << setfill('-') << valid[i] << "------> test case \033[0;31mfail\033[0m" << endl;
        i++;
    }
    i = 0;
    cout << "\033[0;32m---Not-valid-files---\033[0m" << endl;
    while (i < notValidFileCount)
    {
        c_pid = fork();

        if (c_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (c_pid == 0)
        {
            int fd = open("Unit-Tests/cub3D_output", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
            if (fd < 0)
            {
                perror("Failed to open cub3D_output");
                exit(EXIT_FAILURE);
            }

            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);

            str = "./cub3D Unit-Tests/files/Not-Valid/";
            str += notValid[i];
            ptr = str.c_str();
            ret = system(ptr);
            exit(ret != 0 ? EXIT_SUCCESS : EXIT_FAILURE);
        }
        waitpid(c_pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS && ++pass)
            cout << left << setw(50) << setfill('-') << notValid[i] << "------> test case \033[0;32mpass\033[0m" << endl;
        else
            cout << left << setw(50) << setfill('-') << notValid[i] << "------> test case \033[0;31mfail\033[0m" << endl;
        i++;
    }





    cout << "\033[0;32m---result---\033[0m" << endl;
    if (pass != 0 && pass != notValidFileCount + validFileCount)
    {
        cout << "            -----> \033[0;32m" << pass << " passed\033[0m the test "
            << "and \033[0;31m" << notValidFileCount + validFileCount - pass << " failed\033[0m the test" << endl;
    }
    else if (pass == notValidFileCount + validFileCount)
        cout << "            ----->\033[0;32m " << notValidFileCount + validFileCount << " passed\033[0m the test" << endl;
    else if (pass == 0)
        cout << "            ----->\033[0;31m " << notValidFileCount + validFileCount << " failed\033[0m the test" << endl;
    if (pass == notValidFileCount + validFileCount)
        cout << "            ----->cub3D output is in file named '\033[0;32mcub3D_output\033[0m'" << endl;
    else
        cout << "            ----->cub3D output is in file named '\033[0;31mcub3D_output\033[0m'" << endl;
    return 0;
}
