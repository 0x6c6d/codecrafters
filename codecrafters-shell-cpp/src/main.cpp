#include <iostream>
#include <cstdlib> // for getenv
#include <string>
#include <vector>
#include <sstream>
#include <filesystem> // for type command

int main()
{
  // program is called like this: PATH="/usr/bin:/usr/local/bin" ./your_program.sh
  // custom PATH is set as environmental variable of the process that runs the shell
  // env variable can be accessed via getenv()
  const char *path = std::getenv("PATH");
  std::vector<std::string> paths;

  // split PATH by ":" to get a list of paths
  if (path != nullptr)
  {
    std::string pathStr(path);
    std::stringstream ss(pathStr);
    std::string segment;
    while (std::getline(ss, segment, ':'))
    {
      paths.push_back(segment);
    }
  }

  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // REPL (read-eval-print loop)
  while (true)
  {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    // handle exit command (exit or exit 0)
    if (input == "exit" || input == "exit 0")
    {
      return 0;
    }

    // handle echo command
    const std::string echo = "echo ";
    if (input.find(echo) == 0)
    {
      std::string userInput = input.substr(echo.length());
      std::cout << userInput << std::endl;
      continue;
    }

    // handle type command
    const std::string type = "type ";
    if (input.find(type) == 0)
    {
      std::string userInput = input.substr(type.length());

      if (userInput == "echo")
      {
        std::cout << userInput << " is a shell builtin" << std::endl;
        continue;
      }

      if (userInput == "exit")
      {
        std::cout << userInput << " is a shell builtin" << std::endl;
        continue;
      }

      if (userInput == "type")
      {
        std::cout << userInput << " is a shell builtin" << std::endl;
        continue;
      }

      if (path != nullptr)
      {
        bool binFound = false;

        for (const auto &dir : paths)
        {
          std::string binPath = dir + "/" + userInput;
          if (std::filesystem::exists(binPath))
          {
            std::cout << userInput << " is " << binPath << std::endl;
            binFound = true;
            break;
          }
        }
        if (!binFound)
        {
          std::cout << userInput << ": not found" << std::endl;
          binFound = false;
        }
      }
      continue;
    }

    // handle invalid prompts
    std::cout << input << ": command not found\n";
  }
}
