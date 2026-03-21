using Godot;
using AnimalCrossing.Core;

namespace AnimalCrossing.Input;

/// <summary>
/// GameCube controller input mapped to Godot's Input system.
/// Replaces pc_pad.c's SDL2 gamepad + keyboard handling.
///
/// Reads from Godot Input actions defined in project.godot and produces
/// PADStatus structures matching the original GameCube controller format.
///
/// Supports:
///   - Keyboard (configurable via Godot Input Map)
///   - Gamepad (automatic via Godot's joypad support)
///   - Analog sticks (left stick + C-stick) with deadzones
///   - Analog triggers (L/R)
///   - Rumble feedback
/// </summary>
public partial class GCInput : Node
{
    private ushort _currentButtons;
    private ushort _previousButtons;

    // Analog stick values (-128 to 127)
    public sbyte StickX { get; private set; }
    public sbyte StickY { get; private set; }
    public sbyte CStickX { get; private set; }
    public sbyte CStickY { get; private set; }
    public byte TriggerL { get; private set; }
    public byte TriggerR { get; private set; }

    /// <summary>
    /// Poll input and fill PADStatus array.
    /// Called once per frame before game logic.
    /// </summary>
    public void Poll(PadStatus[] pads)
    {
        _previousButtons = _currentButtons;
        _currentButtons = 0;

        // Digital buttons
        if (Godot.Input.IsActionPressed("gc_a"))     _currentButtons |= Constants.PadButtonA;
        if (Godot.Input.IsActionPressed("gc_b"))     _currentButtons |= Constants.PadButtonB;
        if (Godot.Input.IsActionPressed("gc_x"))     _currentButtons |= Constants.PadButtonX;
        if (Godot.Input.IsActionPressed("gc_y"))     _currentButtons |= Constants.PadButtonY;
        if (Godot.Input.IsActionPressed("gc_start")) _currentButtons |= Constants.PadButtonStart;
        if (Godot.Input.IsActionPressed("gc_z"))     _currentButtons |= Constants.PadTriggerZ;
        if (Godot.Input.IsActionPressed("gc_l"))     _currentButtons |= Constants.PadTriggerL;
        if (Godot.Input.IsActionPressed("gc_r"))     _currentButtons |= Constants.PadTriggerR;

        // D-pad
        if (Godot.Input.IsActionPressed("gc_dpad_up"))    _currentButtons |= Constants.PadButtonUp;
        if (Godot.Input.IsActionPressed("gc_dpad_down"))  _currentButtons |= Constants.PadButtonDown;
        if (Godot.Input.IsActionPressed("gc_dpad_left"))  _currentButtons |= Constants.PadButtonLeft;
        if (Godot.Input.IsActionPressed("gc_dpad_right")) _currentButtons |= Constants.PadButtonRight;

        // Main analog stick (keyboard digital → fixed magnitude)
        int sx = 0, sy = 0;
        if (Godot.Input.IsActionPressed("gc_stick_up"))    sy += Constants.StickMagnitude;
        if (Godot.Input.IsActionPressed("gc_stick_down"))  sy -= Constants.StickMagnitude;
        if (Godot.Input.IsActionPressed("gc_stick_left"))  sx -= Constants.StickMagnitude;
        if (Godot.Input.IsActionPressed("gc_stick_right")) sx += Constants.StickMagnitude;

        // Gamepad analog stick (overrides keyboard if present)
        float joyLX = Godot.Input.GetJoyAxis(0, JoyAxis.LeftX);
        float joyLY = Godot.Input.GetJoyAxis(0, JoyAxis.LeftY);
        if (Mathf.Abs(joyLX) > 0.15f) sx = (int)(joyLX * 127);
        if (Mathf.Abs(joyLY) > 0.15f) sy = (int)(-joyLY * 127); // Y is inverted

        StickX = (sbyte)Mathf.Clamp(sx, -128, 127);
        StickY = (sbyte)Mathf.Clamp(sy, -128, 127);

        // C-stick
        int cx = 0, cy = 0;
        if (Godot.Input.IsActionPressed("gc_cstick_up"))    cy += Constants.StickMagnitude;
        if (Godot.Input.IsActionPressed("gc_cstick_down"))  cy -= Constants.StickMagnitude;
        if (Godot.Input.IsActionPressed("gc_cstick_left"))  cx -= Constants.StickMagnitude;
        if (Godot.Input.IsActionPressed("gc_cstick_right")) cx += Constants.StickMagnitude;

        float joyRX = Godot.Input.GetJoyAxis(0, JoyAxis.RightX);
        float joyRY = Godot.Input.GetJoyAxis(0, JoyAxis.RightY);
        if (Mathf.Abs(joyRX) > 0.15f) cx = (int)(joyRX * 127);
        if (Mathf.Abs(joyRY) > 0.15f) cy = (int)(-joyRY * 127);

        CStickX = (sbyte)Mathf.Clamp(cx, -128, 127);
        CStickY = (sbyte)Mathf.Clamp(cy, -128, 127);

        // Analog triggers
        float trigL = Godot.Input.GetJoyAxis(0, JoyAxis.TriggerLeft);
        float trigR = Godot.Input.GetJoyAxis(0, JoyAxis.TriggerRight);
        TriggerL = (byte)(trigL > 0.1f ? (int)(trigL * 255) : 0);
        TriggerR = (byte)(trigR > 0.1f ? (int)(trigR * 255) : 0);
        if (TriggerL > Constants.TriggerThreshold) _currentButtons |= Constants.PadTriggerL;
        if (TriggerR > Constants.TriggerThreshold) _currentButtons |= Constants.PadTriggerR;

        // Fill PAD status for controller 0
        if (pads.Length > 0)
        {
            pads[0].Buttons = _currentButtons;
            pads[0].StickX = StickX;
            pads[0].StickY = StickY;
            pads[0].CStickX = CStickX;
            pads[0].CStickY = CStickY;
            pads[0].TriggerL = TriggerL;
            pads[0].TriggerR = TriggerR;
            pads[0].Error = 0; // PAD_ERR_NONE
        }

        // Other controllers: no connection
        for (int i = 1; i < pads.Length; i++)
        {
            pads[i].Error = 0xFF; // PAD_ERR_NO_CONTROLLER
        }
    }

    /// <summary>Check if a button is currently held.</summary>
    public bool IsButtonHeld(ushort button) => (_currentButtons & button) != 0;

    /// <summary>Check if a button was just pressed this frame.</summary>
    public bool IsButtonPressed(ushort button) =>
        (_currentButtons & button) != 0 && (_previousButtons & button) == 0;

    /// <summary>Check if a button was just released this frame.</summary>
    public bool IsButtonReleased(ushort button) =>
        (_currentButtons & button) == 0 && (_previousButtons & button) != 0;

    /// <summary>Trigger rumble on the gamepad.</summary>
    public void Rumble(float intensity = 1.0f, float duration = 0.2f)
    {
        Godot.Input.StartJoyVibration(0, intensity, intensity, duration);
    }

    /// <summary>Stop rumble.</summary>
    public void StopRumble()
    {
        Godot.Input.StopJoyVibration(0);
    }
}

/// <summary>
/// PADStatus structure matching the original GameCube controller data.
/// </summary>
public class PadStatus
{
    public ushort Buttons;
    public sbyte StickX;
    public sbyte StickY;
    public sbyte CStickX;
    public sbyte CStickY;
    public byte TriggerL;
    public byte TriggerR;
    public byte Error;
}
