#include <time.h>

#include "./cli/driver.h"

int main(){
    srand(time(NULL));

    run_application_menu();
}
