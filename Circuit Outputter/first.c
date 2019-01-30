#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>




typedef struct Node{
	int bit;
	char* name;
	struct Node* next;
} node;

typedef struct graycodeNode{
	int* table;
	int inputs;
	struct graycodeNode* next;
} gcNode;

gcNode* gcHead = NULL;

int powerOfTwo(int power){
	int i;
	int prod = 1;
	if(power == 0)
		return 1;
	for(i = 0;i<power;i++)
		prod *= 2;
	return prod;
}

int findLog(int value){
	int log = 0;
	while(value > 1){
		value /= 2;
		log++;
	}
	return log;
}

//Inserts to front of LL for temps
node* insertLL(int bit,node *head,char* name){

  node *temp = malloc(sizeof(node));
  temp->bit = bit;
  temp->name = name;
  temp->next = head;  
  head = temp;
  //printf("inserted %s\n", name);
  return head;
}

//Data here is the last char of the name used as hash key
void insertHashtable(int data,node *arr[],char* name,int mod,int bit){
	int index = data % mod;
	if(index < 0){
		index = index * -1;
	}
	/*
	node* item = (node*)malloc(sizeof(node));
	item->bit = bit;
	item->name = name;
	item->next = NULL;
	if(arr[index] == NULL){
		arr[index] = malloc(sizeof(node));
		arr[index]->bit = bit;
		arr[index]->name = name;
		arr[index]->next = NULL;
		//printf("inserted %s\n",name);
	} else {
		if(strcmp(arr[index]->name,name)==0) { 
			//printf("updated %s\n",name);
			arr[index]->bit = bit;
			return;
		}
		node *ptr = arr[index];
		while(ptr->next != NULL){
			////printf("%d\n",ptr->data);
			if(strcmp(ptr->name,name)==0){
				//printf("updated %s\n",name);
				ptr->bit = bit;
				return;
			}
			ptr = ptr->next;
		}
		ptr->next = item;
		//printf("inserted %s\n",name);
	}*/

	arr[index] = insertLL(bit,arr[index],name);

}


//data is the last letter of the name used as hash key
int searchHashtable(int data,node *arr[],char* name,int mod){

	int index = data % mod;
	if(index < 0){
		index = index * -1;
	}
	node *ptr = arr[index];
	while(ptr != NULL){
		if(strcmp(ptr->name,name)==0){
			//printf("%s ", ptr->name);
			////printf("present in hashtable\n");
			return ptr->bit;
		} else {
			ptr = ptr->next;
		}
	}
	////printf("absent from hashtable\n");
	return -1;

}



node* updateLL(int bit,node* head,char* name){
	if(head == NULL){
		return head;
	}
	node* ptr = head;
	while(ptr!= NULL){
		if(strcmp(ptr->name,name)==0){
			ptr->bit = bit;
			//printf("updated %s\n", name);
			break;
		}
		ptr = ptr->next;
	}
	return head;

}

//insert to end of LL

node* insertBack(node*head,char* line){

	node* temp = malloc(sizeof(node));
	node* ptr = head;

	temp->name = line;
	temp->next = NULL;


	if(head == NULL){
		head = temp;
		return head;
	}
	
	while(ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = temp;
	return head;

}


//print out LL of temps
void traverse(node * head) {
    if(head == NULL){
      //printf("empty\n");
      return;
    }
    node * ptr = head;
    while (ptr != NULL) {
        //printf("%s\n", ptr->name);
        ptr = ptr->next;
    }
    //printf("\n");
}

int searchLL(node* head,char* name){
	if(head == NULL) return -1;
	if(strcmp(head->name,name)==0){
		////printf("found\n");
		return head->bit;
	}
	node* ptr = head->next;
	while(ptr != NULL){
		if(strcmp(ptr->name,name)==0){
			////printf("found\n");
			return ptr->bit;
		}
		ptr = ptr->next;
	}
	////printf("Not found\n");
	return -1;
}


int* graycode(int inputs){
	int numOfOutputs = powerOfTwo(inputs);
	int* outputs = (int*)malloc(numOfOutputs*sizeof(int));
	int i;
	for(i = 0;i<numOfOutputs;i++){
		outputs[i] = i ^ (i >> 1);
	}
	return outputs;
}


void gcinsertLL(int inputs,int* table){

  gcNode *temp = malloc(sizeof(gcNode));
  temp->table = table;
  temp->inputs = inputs; 
  temp->next = gcHead;
  gcHead = temp;
  //printf("inserted %s\n", name);
}

int* gcsearchLL(int inputs){
	if(gcHead == NULL) return NULL;
	if(gcHead->inputs == inputs){
		////printf("found\n");
		return gcHead->table;
	}
	gcNode* ptr = gcHead->next;
	while(ptr != NULL){
		if(ptr->inputs == inputs){
			////printf("found\n");
			return ptr->table;
		}
		ptr = ptr->next;
	}
	////printf("Not found\n");
	return NULL;
}

int not(int in){
	if(in == 1) return 0;
	else if(in == 0) return 1;
	else return -1;
}

int and(int in1, int in2){
	if(in1 == 1 && in2 == 1) return 1;
	return 0;
}

int or(int in1, int in2){
	if(in1 == 0 && in2 == 0) return 0;
	return 1;
}

int nand(int in1, int in2){
	if(in1 == 1 && in2 == 1) return 0;
	return 1;
}

int nor(int in1, int in2){
	if(in1 == 0 && in2 == 0) return 1;
	return 0;
}

int xor(int in1, int in2){
	if((in1 == 0 && in2 == 0) || (in1 == 1 && in2 == 1)) return 0;
	return 1;
}

int binaryToDecimal(int n){
    int num = n;
    int value = 0;    
    int base = 1;
     
    int temp = num;
    while(temp){
        int lastDigit = temp % 10;
        temp = temp/10;
        value += lastDigit*base;
        base = base*2;
    }
     
    return value;
}

int concatenate(int x, int y) {
    int pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

int* decoder(int inputs,int* inValues){
	int twoPowerInput = powerOfTwo(inputs);

	int* graycodeInput = gcsearchLL(inputs);
	if(graycodeInput == NULL){
		graycodeInput = graycode(inputs);
		gcinsertLL(inputs,graycodeInput);
	}
	int* outputs = (int*)malloc(twoPowerInput*sizeof(int));
	int inVal = 0;
	int i,j;
	for(i = 0;i<inputs;i++){
		inVal = concatenate(inVal,inValues[i]);
	}
	inVal = binaryToDecimal(inVal);
	////printf("%d\n", inVal);
	for(i = 0;i<twoPowerInput;i++){
		if(inVal == graycodeInput[i]) break;
	}

	for(j = 0;j<twoPowerInput;j++){
		if(i == j){
			outputs[j] = 1;
		} else {
			outputs[j] = 0;
		}
	}

	return outputs;
}

int mux(int inputs,int numOfSelectors,int* inValues,int* selectors){
	int output = 0;
	int twoPowerInput = powerOfTwo(inputs);
	int* graycodeInput = gcsearchLL(inputs);
	if(graycodeInput == NULL){
		graycodeInput = graycode(inputs);
		gcinsertLL(inputs,graycodeInput);
	}
	int i;
	int selVal = 0;
	for(i = 0;i<numOfSelectors;i++){
		selVal = concatenate(selVal,selectors[i]);
	}
	selVal = binaryToDecimal(selVal);

	for(i = 0;i<twoPowerInput;i++){
		if(selVal == graycodeInput[i]) break;
	}

	output = inValues[i];
	return output;

}

int main(int argc,char** argv){

	
	char* line = malloc(200*sizeof(char));
	int numOfInputs;
	int numOfOutputs;
	char* token;
	int i,j;
	node* inputs[50];
	node* outputs[50];
	char* tempString;



	FILE *fp;
	fp = fopen(argv[1],"r");

	//GET NUMBER OF INPUTS
	fgets(line,200,fp);
	tempString = strdup(line);
	token = strtok(tempString," \n");
	token = strtok(NULL," \n");
	numOfInputs = atoi(token);
	//printf("IN: %d\n", numOfInputs);
	char* nameOfIns[numOfInputs];
	//make hashtable of inputs
	for(i = 0;i<numOfInputs;i++){
		token = strtok(NULL," \n");
		nameOfIns[i] = token;
		insertHashtable(token[strlen(token)-1],inputs,token,50,0);
		//searchHashtable(token[strlen(token)-1],inputs,token,50);
	}


	//GET NUMBER OF OUTPUTS
	fgets(line,200,fp);
	tempString = strdup(line);
	token = strtok(tempString," \n");
	token = strtok(NULL," \n");
	numOfOutputs = atoi(token);
	//printf("OUT: %d\n", numOfOutputs);
	char* nameOfOuts[numOfOutputs];
	for(i = 0;i<numOfOutputs;i++){
		token = strtok(NULL," \n");
		nameOfOuts[i] = token;
		insertHashtable(token[strlen(token)-1],outputs,token,50,0);
		//searchHashtable(token[strlen(token)-1],outputs,token,50);
	}
	

	//truthTable rows & columns
	int twoPowerInput = powerOfTwo(numOfInputs);
	int truthTableCols = numOfInputs+numOfOutputs;

	//creat graycode table for inputs
	int* graycodeTable = (int*)malloc(twoPowerInput*sizeof(int));
	graycodeTable = graycode(numOfInputs);
	gcinsertLL(numOfInputs,graycodeTable);


	//MAKE TRUTHTABLE 2D ARRAY
	int **truthTable = (int**)malloc(twoPowerInput * sizeof(int*));
	for(i = 0;i < twoPowerInput ;i++){
		truthTable[i] = (int*)malloc((truthTableCols)* sizeof(int));
	}


	int val;
	for(i = 0;i<twoPowerInput;i++){
		val = graycodeTable[i];
		for(j = truthTableCols-1;j>=0;j--){
			if(j < numOfInputs){
				truthTable[i][j] = val%2;
				val = val/2;
			} else {
				truthTable[i][j] = 0;
			}

		}
	}

	//printf("TRUTHTABLE\n");
	for(i = 0;i<twoPowerInput;i++){
		for(j = 0;j<truthTableCols;j++){
			//printf("%d ", truthTable[i][j]);
		}
		//printf("\n");
	}

	node* instructions = NULL;
	
	while(fgets(line,200,fp) != NULL){
		
		line = strtok(line,"\n");
		tempString = strdup(line);
		instructions = insertBack(instructions,tempString);
	}
	//printf("OPERATIONS\n");
	traverse(instructions);
	
	
	//LL for temps
	node* temp = NULL;
	
	char* op;
	char* in1Name;
	char* in2Name;
	char* outName;
	int in1=0;
	int in2=0;
	int out=0;
	int insertOut;
	int k;
	int decoderNumOfIns;
	int muxNumOfIns;
	int numOfSelectors;

	//int* finalOut[numOfOutputs];
	//insert all instructions into LL
	for(i = 0;i<twoPowerInput;i++){
		for(j = 0;j<numOfInputs;j++){
			insertHashtable(nameOfIns[j][strlen(nameOfIns[j])-1],inputs,nameOfIns[j],50,truthTable[i][j]);
		}
		temp = NULL;
		node* ptr = instructions;
		while(ptr != NULL){
			tempString = strdup(ptr->name);
			//printf("LINE: %s\n", tempString);
			op = strtok(tempString," ");
			//printf("OP: %s\n", op);
			if(strcmp(op,"NOT")==0){
				in1Name = strtok(NULL," ");
				outName = strtok(NULL," \n");
				//printf("in1Name: %s\n", in1Name);
				//printf("outName: %s\n", outName);
				if(isupper(in1Name[0])){
					in1 = searchHashtable(in1Name[strlen(in1Name)-1],inputs,in1Name,50);
				} else if (islower(in1Name[0])){
					in1 = searchLL(temp,in1Name);	
				} else {
					in1 = atoi(in1Name);
				}
				if(in1 == -1){
					in1 = atoi(in1Name);
				}
				out = not(in1);
				if(isupper(outName[0])){ //OUT
					insertHashtable(outName[strlen(outName)-1],outputs,outName,50,out);
				} else { //temp
					insertOut = searchLL(temp,outName);
					if(insertOut == -1){ //doesnt exist
						temp = insertLL(out,temp,outName);
					} else {
						temp = updateLL(out,temp,outName);
					}

				}
			} else if(strcmp(op,"DECODER")!=0 && strcmp(op,"MULTIPLEXER") != 0){ //not decoder or mux
				in1Name = strtok(NULL," ");
				in2Name = strtok(NULL," ");
				outName = strtok(NULL," \n");
				//printf("in1Name: %s\n", in1Name);
				//printf("in2Name: %s\n", in2Name);
				//printf("outName: %s\n", outName);
				
				/*in1 = searchHashtable(in1Name[strlen(in1Name)-1],inputs,in1Name,50); //search hash
				if(in1 == -1){ //not in hash
					in1 = searchLL(temp,in1Name);
				} 
				if(in1 == -1) { //either a 1 or 0
					in1 = atoi(in1Name);
				}
				in2 = searchHashtable(in2Name[strlen(in2Name)-1],inputs,in2Name,50); //search hash
				if(in2 == -1){ //not in hash
					in2 = searchLL(temp,in2Name);
				} 
				if(in2 == -1){ //either a 1 or 0
					in2 = atoi(in2Name);
				}*/
				if(isupper(in1Name[0])){
					in1 = searchHashtable(in1Name[strlen(in1Name)-1],inputs,in1Name,50);
				} else if (islower(in1Name[0])){
					in1 = searchLL(temp,in1Name);	
				} else {
					in1 = atoi(in1Name);
				}
				if(in1 == -1){
					in1 = atoi(in1Name);
				}
				if(isupper(in2Name[0])){
					in2 = searchHashtable(in2Name[strlen(in2Name)-1],inputs,in2Name,50); //search hash
				} else if (islower(in2Name[0])){
					in2 = searchLL(temp,in2Name);
				} else {
					in2 = atoi(in2Name);
				}
				if(in2 == -1){
					in2 = atoi(in2Name);
				}
				//printf("\n");
				//printf("%s: %d\n",in1Name, in1);
				//printf("%s: %d\n", in2Name,in2);

				if(strcmp(op,"AND")==0){
					out = and(in1,in2);
				} else if(strcmp(op,"OR")==0){
					out = or(in1,in2);
				} else if(strcmp(op,"NAND")==0){
					out = nand(in1,in2);
				} else if(strcmp(op,"NOR")==0){
					out = nor(in1,in2);
				} else if(strcmp(op,"XOR")==0){
					out = xor(in1,in2);
				} 
				//printf("out: %d\n",out);

				if(isupper(outName[0])){ //OUT
					insertHashtable(outName[strlen(outName)-1],outputs,outName,50,out);
				} else { //temp
					insertOut = searchLL(temp,outName);
					if(insertOut == -1){ //doesnt exist
						temp = insertLL(out,temp,outName);
					} else {
						temp = updateLL(out,temp,outName);
					}

				}



			} else if(strcmp(op,"DECODER")==0){
				decoderNumOfIns = atoi(strtok(NULL," "));
				int* ins = (int*)malloc(decoderNumOfIns*sizeof(int));
				for(k = 0;k<decoderNumOfIns;k++){
					in1Name = strtok(NULL," ");
					if(isupper(in1Name[0])){
						in1 = searchHashtable(in1Name[strlen(in1Name)-1],inputs,in1Name,50);
					} else if (islower(in1Name[0])){
						in1 = searchLL(temp,in1Name);	
					} else {
						in1 = atoi(in1Name);
					}
					if(in1 == -1){
						in1 = atoi(in1Name);
					}
					ins[k] = in1;
				}
				//printf("HUR\n");
				for(k = 0;k<decoderNumOfIns;k++){
					//printf("%d ",ins[k] );
				}
				//printf("DONE\n");
				int numOfOutsDecoder = powerOfTwo(decoderNumOfIns);
				char* outNamesDecoder[numOfOutsDecoder];
				for(k = 0;k<numOfOutsDecoder;k++){
					outNamesDecoder[k] = strtok(NULL," \n");
				}
				int* outsDecoder = (int*)malloc(numOfOutsDecoder*sizeof(int));
				outsDecoder = decoder(decoderNumOfIns,ins);
				//printf("OUTS\n");
				for(k = 0;k<numOfOutsDecoder;k++){
					//printf("%d ",outsDecoder[k]);
				}
				//printf("DONE AGAIN\n");
				for(k = 0;k<numOfOutsDecoder;k++){
					if(isupper(outNamesDecoder[k][0])){ //OUT
						insertHashtable(outNamesDecoder[k][strlen(outNamesDecoder[k])-1],outputs,outNamesDecoder[k],50,outsDecoder[k]);
					}
					else { //temp
						insertOut = searchLL(temp,outNamesDecoder[k]);
	
						if(insertOut == -1){ //doesnt exist
							temp = insertLL(outsDecoder[k],temp,outNamesDecoder[k]);
						} else {
							temp = updateLL(outsDecoder[k],temp,outNamesDecoder[k]);
						}
					}
				}

				

			} else { //MUX
				muxNumOfIns = atoi(strtok(NULL," "));
				numOfSelectors = findLog(muxNumOfIns);
				int* ins = (int*)malloc(muxNumOfIns*sizeof(int));
				int* selectors = (int*)malloc(numOfSelectors*sizeof(int));
				for(k = 0;k<muxNumOfIns;k++){
					in1Name = strtok(NULL," ");
					if(isupper(in1Name[0])){
						in1 = searchHashtable(in1Name[strlen(in1Name)-1],inputs,in1Name,50);
					} else if (islower(in1Name[0])){
						in1 = searchLL(temp,in1Name);	
					} else {
						in1 = atoi(in1Name);
					}
					if(in1 == -1){
						in1 = atoi(in1Name);
					}
					ins[k] = in1;
					//printf("%d ",ins[k]);
				}
				//printf("\n");
				for(k = 0;k<numOfSelectors;k++){
					in1Name = strtok(NULL," "); //SELECTORS
					if(isupper(in1Name[0])){
						in1 = searchHashtable(in1Name[strlen(in1Name)-1],inputs,in1Name,50);
					} else if (islower(in1Name[0])){
						in1 = searchLL(temp,in1Name);	
					} else {
						in1 = atoi(in1Name);
					}
					if(in1 == -1){
						in1 = atoi(in1Name);
					}
					selectors[k] = in1;
					//printf("%d ",selectors[k] );
				}

				outName = strtok(NULL," \n");
				out = mux(muxNumOfIns,numOfSelectors,ins,selectors);
				//printf("out %d\n", out);

				if(isupper(outName[0])){ //OUT
					insertHashtable(outName[strlen(outName)-1],outputs,outName,50,out);
				} else { //temp
					insertOut = searchLL(temp,outName);
					if(insertOut == -1){ //doesnt exist
						temp = insertLL(out,temp,outName);
					} else {
						temp = updateLL(out,temp,outName);
					}

				}


			}


			/*node* ptr2 = temp;
			while(ptr2 != NULL){
				//printf("%s: %d -> ",ptr2->name,ptr2->bit);
				ptr2 = ptr2->next;
			}*/
			//printf("\n");
			//printf("----------------\n");

			ptr = ptr->next;
		}
		//printf("==========================\n");
		k = 0;
		for(j = numOfInputs;j<truthTableCols;j++){
			truthTable[i][j] = searchHashtable(nameOfOuts[k][strlen(nameOfOuts[k])-1],outputs,nameOfOuts[k],50);
			k++; 
		}
	}

	//printf("\n");
	for(i = 0;i<twoPowerInput;i++){
		for(j = 0;j<truthTableCols;j++){
			printf("%d ", truthTable[i][j]);
		}
		printf("\n");
	}

	/*gcNode* ptr2 = gcHead;
	while(ptr2 != NULL){
		printf("%d -> ",ptr2->inputs);
		ptr2 = ptr2->next;
	}
	printf("\n");
	*/
	

	return 0;
}