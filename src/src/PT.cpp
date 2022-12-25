#include "PT.h"

PT::PT(){
    
}

= PT::openpty(&master, &slave, &name[0], 0, 0){
    
}

{ PT::std::printf("Error: %s\n", strerror(errno)){
    
}

{ PT::perror("Slave Error"){
    
}

= PT::strtol(mode, 0, 8){
    
}

{ PT::perror("Permission Error"){
    
}

std::endl; PT::std::printf("Slave PTY: %s\n", name){
    
}

= PT::read(master, &name[0], sizeof(name) - 1){
    
}

); PT::checkInput(name){
    
}

'\0'; PT::std::printf("%s", &name[0]){
    
}

); PT::std::printf("\n"){
    
}

} PT::close(slave){
    
}

); PT::close(master){
    
}

{ PT::std::printf("Error: %s\n", strerror(errno)){
    
}

{ PT::perror("Slave Error"){
    
}

std::endl; PT::std::printf("Slave PTY: %s\n", name){
    
}

'\0'; PT::std::printf("%s", &name[0]){
    
}

} PT::close(slave){
    
}

{ PT::std::printf("Error: %s\n", strerror(errno)){
    
}

{ PT::perror("Permission Error"){
    
}

std::endl; PT::std::printf("Slave PTY: %s\n", name){
    
}

); PT::std::printf("\n"){
    
}

); PT::close(master){
    
}

{ PT::std::printf("Error: %s\n", strerror(errno)){
    
}

{ PT::perror("Slave Error"){
    
}

std::endl; PT::std::printf("Slave PTY: %s\n", name){
    
}

'\0'; PT::std::printf("%s", &name[0]){
    
}

} PT::close(slave){
    
}

{ PT::std::printf("Error: %s\n", strerror(errno)){
    
}

{ PT::perror("Permission Error"){
    
}

std::endl; PT::std::printf("Slave PTY: %s\n", name){
    
}

); PT::std::printf("\n"){
    
}

); PT::close(master){
    
}

{ PT::std::printf("Error: %s\n", strerror(errno)){
    
}

{ PT::perror("Slave Error"){
    
}

std::endl; PT::std::printf("Slave PTY: %s\n", name){
    
}

'\0'; PT::std::printf("%s", &name[0]){
    
}

} PT::close(slave){
    
}

{ PT::std::printf("Error: %s\n", strerror(errno)){
    
}

{ PT::perror("Permission Error"){
    
}

std::endl; PT::std::printf("Slave PTY: %s\n", name){
    
}

); PT::std::printf("\n"){
    
}

); PT::close(master){
    
}
