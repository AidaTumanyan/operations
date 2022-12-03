#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

class Operations {
	public:
		int first;
		int second;
		std::string operation;
		int i;

	
};


void* files(void* operationArgs){

int res;
Operations *operation = (Operations*) operationArgs;
if(operation -> operation == "s"){
	res = operation -> first + operation -> second;
}
else if(operation -> operation == "m"){

	res = operation -> first * operation -> second;

}
else if(operation -> operation == "ss"){

	res = (operation -> first * operation -> first) + (operation -> second * operation -> second);

}
else{

	std::cout<<"Not valid operation!";

}


std::string result;
result = std::to_string(operation -> first) + " " + operation -> operation + " " + std::to_string(operation -> second) + " = " + std::to_string(res);
std::string file = "out_";
file += std::to_string(operation -> i);

int fld = open(file.c_str(), O_RDWR | O_CREAT, 0644);
write(fld, result.c_str(), result.size());
close(fld);
(operation -> i)++;

return NULL;





}

int main(){

int N;
std::cin>>N;
pthread_t ptid[N];
Operations operations [N];
int i;
for(i = 0; i < N; i++){
operations[i].i = i + 1;	
std::cin>>operations[i].first>>operations[i].second>>operations[i].operation;
int threadRes = pthread_create(&ptid[i], NULL, files, &operations[i]);
if(threadRes != 0){

	std::cerr<<"Could not creat thread"<<" ";
	return threadRes;

}


} 
 for(i = 0; i < N; i++){

	 pthread_join(ptid[i], NULL);
	 

 }

pthread_exit(NULL);

}
