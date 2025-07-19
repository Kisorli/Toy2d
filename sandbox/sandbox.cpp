#include<cstdlib>

#include<Application.h>

int main()
{
    Application* app = new Application();
    app->run();
    delete app;
    return EXIT_SUCCESS;
}