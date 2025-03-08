#include <iostream>
#include <cstring>
#include <filesystem>
#include <vector>
#include <string>

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

namespace fs = std::filesystem;
using namespace ftxui;

int main(int argc, char* argv[]) {
    std::string name;
    auto screen = ScreenInteractive::TerminalOutput();
    auto input = Input(&name, "Enter name...");
    auto button = Button("Submit", [&] {
        screen.ExitLoopClosure()(); // Close UI when submitted
    });

    std::string path = ".";

    std::vector<std::string> files;
    std::vector<std::string> folders;
    std::vector<Component> folder_buttons;

    // Process command-line arguments
    for (int i = argc - 1; i >= 0; i--) {
        if (std::strcmp(argv[i], "--version") == 0) {
            std::cout << "Version 1.0" << std::endl;
            return 0;
        } else if (std::strcmp(argv[i], "--help") == 0) {
            std::cout << "Usage: " << argv[0] << " [options] [file]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "\t--help  Display All Commands" << std::endl;
            std::cout << "\t--version  Display Version" << std::endl;
            return 0;
        }
    }

    // Generate file content
    for (const auto &entry : fs::directory_iterator(".")) {
        if (fs::is_directory(entry.path())) {
            folders.push_back(entry.path().filename().string());
        } else if (fs::is_regular_file(entry.path())) {
            files.push_back(entry.path().filename().string());
        }
    }

    // Create buttons for folders
    for (int i = 0; i < folders.size(); i++) {
        folder_buttons.push_back(Button(folders[i] + " (Open)", [&, i] {
            std::cout << "Opening folder: " << folders[i] << std::endl;
        }));
    }

    // Renderer
    auto renderer = Renderer([&] {
        Elements folder_elements;
        for (auto& button : folder_buttons) {
            folder_elements.push_back(button->Render());
        }

        return vbox({
            text("Enter your name:"),
            input->Render(),
            separator(),
            button->Render(),
            separator(),
            vbox(std::move(folder_elements)),
        }) | border;
    });

    screen.Loop(renderer);

    return 0;
}