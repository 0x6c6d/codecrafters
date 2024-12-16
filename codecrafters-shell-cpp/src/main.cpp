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
