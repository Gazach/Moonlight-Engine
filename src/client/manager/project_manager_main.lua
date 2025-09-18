-- This script is the main entry point for the project manager window.
local current_dir = debug.getinfo(1, "S").source:match("@(.*)[/\\]") -- Get the current directory of this script
dofile(current_dir .. "/../helper/gui_builder.lua") -- Load the GUI builder helper functions

print("This is the project manager main script.")
LoggerDebug("Lua script executed successfully.")

-- This function is called every frame to update the GUI

function update() 
    Panel(20, 20, 200, 100, "#ff3939ff",
        PanelOptions():SetBorderOptions(
                    PanelBorderOptions():SetEnabled(true)
                                        :SetThickness(3)
                                        :SetColor("#00ff00ff")))
end