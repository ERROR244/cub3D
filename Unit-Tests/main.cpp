#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <iomanip>

using namespace std;

int main(void)
{
    const char *valide[] =
    {
        "Unit-Tests/files/Valid/tester_order1.cub", "Unit-Tests/files/Valid/tester_order2.cub",
        "Unit-Tests/files/Valid/tester_order3.cub", "Unit-Tests/files/Valid/tester_order4.cub",
        "Unit-Tests/files/Valid/tester_order5.cub", "Unit-Tests/files/Valid/tester_order6.cub", nullptr
    };
    const char *notValide[] =
    {
        "Unit-Tests/files/Not-Valid/closed_map0.cub", "Unit-Tests/files/Not-Valid/closed_map1.cub", "Unit-Tests/files/Not-Valid/closed_map2.cub", "Unit-Tests/files/Not-Valid/closed_map3.cub",
        "Unit-Tests/files/Not-Valid/closed_map4.cub", "Unit-Tests/files/Not-Valid/closed_map5.cub", "Unit-Tests/files/Not-Valid/closed_map6.cub", "Unit-Tests/files/Not-Valid/closed_map7.cub",
        "Unit-Tests/files/Not-Valid/closed_map8.cub", "Unit-Tests/files/Not-Valid/closed_map9.cub", "Unit-Tests/files/Not-Valid/color_error0.cub", "Unit-Tests/files/Not-Valid/color_error1.cub",
        "Unit-Tests/files/Not-Valid/map_character0.cub", "Unit-Tests/files/Not-Valid/map_character1.cub", "Unit-Tests/files/Not-Valid/map_character2.cub", "Unit-Tests/files/Not-Valid/map_character3.cub",
        "Unit-Tests/files/Not-Valid/map_character4.cub", "Unit-Tests/files/Not-Valid/map_character5.cub", "Unit-Tests/files/Not-Valid/map_character6.cub", "Unit-Tests/files/Not-Valid/map_character7.cub",
        "Unit-Tests/files/Not-Valid/map_character8.cub", "Unit-Tests/files/Not-Valid/map_character9.cub", "Unit-Tests/files/Not-Valid/name_error0.ubc", "Unit-Tests/files/Not-Valid/name_error1,cub",
        "Unit-Tests/files/Not-Valid/name_error2.cab", "Unit-Tests/files/Not-Valid/name_error3.cubb", "Unit-Tests/files/Not-Valid/name_error4.cub.buc", "Unit-Tests/files/Not-Valid/order0.cub",
        "Unit-Tests/files/Not-Valid/order1.cub", "Unit-Tests/files/Not-Valid/order2.cub", "Unit-Tests/files/Not-Valid/order3.cub", "Unit-Tests/files/Not-Valid/order4.cub",
        "Unit-Tests/files/Not-Valid/order5.cub", "Unit-Tests/files/Not-Valid/order6.cub", nullptr
    };

    pid_t c_pid;
    string str;
    const char *ptr;
    int i = 0;
    int status;
    int ret = 0;
    int pass = 0;

    unlink("Unit-Tests/cub3D_output");
    cout << "\033[0;32m---valid-files---\033[0m" << endl;
    while (valide[i] != nullptr)
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

            str = "./cub3D ";
            str += valide[i];
            ptr = str.c_str();
            ret = system(ptr);
            exit(ret != 0 ? EXIT_FAILURE : EXIT_SUCCESS);
        }
        waitpid(c_pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS && ++pass)
            cout << left << setw(50) << setfill('-') << valide[i] << "------>test case \033[0;32mpass\033[0m" << endl;
        else
            cout << left << setw(50) << setfill('-') << valide[i] << "------>test case \033[0;31mfail\033[0m" << endl;
        i++;
    }
    i = 0;
    cout << "\033[0;32m---Not-valid-files---\033[0m" << endl;
    while (notValide[i] != nullptr)
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

            str = "./cub3D ";
            str += notValide[i];
            ptr = str.c_str();
            ret = system(ptr);
            exit(ret != 0 ? EXIT_SUCCESS : EXIT_FAILURE);
        }
        waitpid(c_pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS && ++pass)
            cout << left << setw(50) << setfill('-') << notValide[i] << "------>test case \033[0;32mpass\033[0m" << endl;
        else
            cout << left << setw(50) << setfill('-') << notValide[i] << "------>test case \033[0;31mfail\033[0m" << endl;
        i++;
    }
    cout << "\033[0;32m---result---\033[0m" << endl;
    if (pass != 0 && pass != 40)
    {
        cout << "            -----> \033[0;32m" << pass << " passed\033[0m the test "
            << "and \033[0;31m" << 40 - pass << " failed\033[0m the test" << endl;
    }
    else if (pass == 40)
        cout << "            ----->\033[0;32m 40 passed\033[0m the test" << endl;
    else if (pass == 0)
        cout << "            ----->\033[0;31m 40 failed\033[0m the test" << endl;
    if (pass == 40)
        cout << "            ----->cub3D output is in file named '\033[0;32mcub3D_output\033[0m'" << endl;
    else
        cout << "            ----->cub3D output is in file named '\033[0;31mcub3D_output\033[0m'" << endl;
    return 0;
}
