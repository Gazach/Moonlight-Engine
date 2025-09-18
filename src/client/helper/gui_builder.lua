-- gui_builders.lua

function PanelBorderOptions()
    local self = {
        enabled = false,
        thickness = 1,
        color = "#000000ff"
    }

    function self:SetEnabled(val) self.enabled = val; return self end
    function self:SetThickness(val) self.thickness = val; return self end
    function self:SetColor(val) self.color = val; return self end

    return self
end

function PanelOptions()
    local self = {
        border = PanelBorderOptions()
    }

    function self:SetBorderOptions(borderOpts)
        self.border = borderOpts
        return self
    end

    return self
end
