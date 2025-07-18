class Sandbox
{
public:
    Sandbox()
    {

    }
    ~Sandbox()
    {

    }
};

int main()
{
    Sandbox* sandbox = new Sandbox();
    delete sandbox;
    return 0;
}