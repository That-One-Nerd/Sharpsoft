# Sharpsoft

Sharpsoft is a UI engine for the Vex V5 brain. It's based off the way Windows Forms functions in .NET. It is compatible with Pros and (will be) compatible with Vexcode as well. I'm still working on it, it's nowhere close to finished and still quite far from an actual release, but I'll get to it.

You can use this project for whatever you want. Just credit me.

## Use

To use Sharpsoft, copy the sharpsoft folders in both the `include` and the `src` directories. Paste them into your projects. It should just compile.

In the code, you can use pre-existing window types or create your own. If you make your own, just make the class derive from `sharp::window_base` and add a paint method, like this:

```c++
class custom_window : public window_base
{
protected:
    void paint() override
    {
        // Rendering code goes here.
    }
    void tick() override
    {
        // Tick code goes here.
    }

public:
    //                             <Title>       <Position>             <Size>
    custom_window() : window_base("Custom", sharp::int2(50, 50), sharp::int2(250, 200))
    {
        // Initialization code goes here.
    }
};
```

There are lots of ways to customize the windows. You can modify the styles with `style()`, resize, change titles, and more. It's important to note that a window does not refresh every frame by default. To do that, you need to set a specific flag.

```c++
custom_window() : window_base("Custom", sharp::int2(50, 50), sharp::int2(250, 200))
{
    // This doesn't have to be in the constructor but it's probably best there.
    set_flag(CONTINUOUS_PAINT, true);

    // You can also change the tick loop here.
    set_flag(CONTINUOUS_TICK, false); // Defaults to `true`.
}
```

And using the windows is even easier. Here's how Sharpsoft setup usually looks:

```c++
void initialize()
{
    sharp::initialize();
    sharp::add_window(custom_window());
    // More windows would go here.
    sharp::start();
}
```

Not that bad, right? There are some weird edge cases but I'll iron them out as I find them.
Hope you enjoy using it!
