// Admin Passcode to view customer Details = 1234

#include <stdio.h>
#include <string.h>
struct room {
	int room_no;
	char room_type[7];
};
struct customer {
	char name[30];
	int age, nights_stayed, room_code, amount;	
};
int booking(struct customer c[],int len,struct room r[]) {
	int i,exist=0,room_type, amount, tax, cost_night, success;
	printf("-----< Please Fill the Details below >-----\n");
	do{
		printf("Enter Name : ");
		scanf("%s",c[len].name);
		for(i=0; i<len; i++) {
			if(strcmp(c[i].name,c[len].name) == 0) {
				exist=1;
				printf("--< Customer already Exist >--\n");
				break;
			}
			else exist=0;
		}
	}while(exist == 1);
	printf("Enter Age : ");
	scanf("%d",&c[len].age);
	printf("Enter how many night's do you wish to stay : ");
	scanf("%d",&c[len].nights_stayed);
	c[len].room_code = len;
	exist=0;
	do{
		printf("Enter what room type (1. single, 2. double, 3. family) do you wish to stay : ");
		scanf("%d",&i);
		if((i == 1)||(i == 2)||(i == 3)) exist=1;
		else {
			printf("--< Wrong Numeric code entered >--\n");
			exist=0;
		};
	}while(exist==0);
	if(i == 1)  { strcpy(r[c[len].room_code].room_type, "Single"); cost_night=2000;}
	else if(i == 2)  { strcpy(r[c[len].room_code].room_type, "Double"); cost_night=5000;}
	else { strcpy(r[c[len].room_code].room_type, "Family"); cost_night=7000;}
	tax = cost_night * 0.05;
	amount = (cost_night + tax)*c[len].nights_stayed;
	printf("---------------------------------------------------------\n");
	printf("Room Type    Cost/night    Tax      No. of Night's Stayed\n");
	printf("---------------------------------------------------------\n");
	printf(" %s        %d         %d                 %d     \n",r[c[len].room_code].room_type,cost_night,tax,c[len].nights_stayed);
	printf("---------------------------------------------------------\n");
	printf("Total Amount = %d, Do you wish to Proceed (1. Yes, 2. No) : ",amount);
	exist=0;
	c[len].amount=amount;
	do{
		scanf("%d",&i);
		if(i == 1) { printf("\n---< Room has been Booked >---\n"); exist=1; success=1;}
		else if(i == 2) { printf("\n---< Room is not being Booked >---\n",c[len].room_code); exist=1; success=0;}
		else { printf("Wrong Input code entered, Enter Correct Code : "); exist=0;}
	}while(exist == 0);
	return success;
}
void check_in(struct customer c[], int len) {
	int i, j;
    struct customer temp;
    for (i = 0; i < len - 1; i++) {
        for (j = i + 1; j < len; j++) {
            if (strcmp(c[i].name, c[j].name) > 0) {
                temp = c[i];
                c[i] = c[j];
                c[j] = temp;
            }
        }
    }
}
void check_out(struct customer c[], int len, char name[], int j) {
	int i;
        for (i = j; i < len - 1; i++) {
               c[i] = c[i + 1];
    }
}
void main() {
	int input,sin_room=15,dou_room=10,fam_room=5,c_len=0,i,j,exist;
	char temp[30];
	struct room r[30]; struct customer c[30];
//  Example (two customers) >----------
	c_len+=2; strcpy(c[0].name, "Raj"); c[0].age=45; c[0].nights_stayed=3;c[0].room_code=0; r[0].room_no=1; strcpy(r[0].room_type, "Single"); c[0].amount=3000;
	strcpy(c[1].name, "Hari"); c[1].age=65; c[1].nights_stayed=2;c[1].room_code=1; r[1].room_no=2; strcpy(r[1].room_type, "Single");c[1].amount=5000;
	sin_room-=2;
//  -------------------
	printf("-----< Welcome to Hotel Grand >-----\n");
	do{
		printf("\n---< Please Enter Numeric Code adjacent to Action provided below >---\n");
		printf("1. Check all Rooms availability\n2. Check Specific Room availability\n3. Check Customer Details\n4. Book a room\n5. Cancel a booking\n6. Exit\n");
		printf("Enter a Input Code : ");
		scanf("%d",&input);
		switch(input) {
			case 1:
				printf("------------------------------\n");
				printf(" Room type    Available Rooms");
				printf("\n------------------------------\n");
				printf("  Single            %d\n",sin_room);
				printf("  Double            %d\n",dou_room);
				printf("  Family            %d\n",fam_room);
				printf("------------------------------\n");
				printf("Rooms already Taken ( 1 - 30 ) -> [ ");
				for(i=0; i<c_len;i++) printf("%d, ",r[c[i].room_code].room_no);
				printf("]\n------------------------------");
				break;
			case 2:
				printf("Enter which Room to be Checked ( 1 - 30 ) : ");
				do{
					scanf("%d",&j);
					if ((j<1)||(j>30)) printf("---< Wrong Room Number Entered, Enter ( 1 - 30 ) : ");
				}while((j<1)||(j>30));
				exist=0;
				for(i=0; i<c_len; i++) {
					if(r[c[i].room_code].room_no == j) exist=i+1;
				}
				if(exist==0) printf("\n---< Room has not been Taken >---\n");
				else  printf("\n---< Room has been Taken by Customer -> %s >---\n",c[exist-1].name);
				break;
			case 3:
				do{
					printf("Enter Admin Numeric Passcode (0 - Quit) : ");
					scanf("%d",&i);
					if((i!=0)&&(i!=1234)) printf("---< Wrong Passcode >---\n");
				}while((i!=0)&&(i!=1234));
				if(i==1234) {
					printf("-----------------------------------------------------\n");
					printf("S.no      Name     Age     Room No.    Room type    Night's Stayed     Amount Paid");
					printf("\n-----------------------------------------------------\n");
					for(i=0; i<c_len; i++) printf("%d.       %s     %d          %d        %s          %d               %d\n",i+1,c[i].name,c[i].age,r[c[i].room_code].room_no,r[c[i].room_code].room_type,c[i].nights_stayed,c[i].amount);
					printf("------------------------------------------------------");
				}
				break;
			case 4:
				i = booking(c,c_len,r);
				if(i == 1) {
					if(strcmp(r[c[c_len].room_code].room_type,"Single") == 0) { 
					r[c[c_len].room_code].room_no= 15-sin_room; 
					sin_room--; 
					}
					else if(strcmp(r[c[c_len].room_code].room_type,"Double") == 0) { 
					r[c[c_len].room_code].room_no= 25-dou_room; 
					dou_room--; 
					}
					if(strcmp(r[c[c_len].room_code].room_type,"Family") == 0) { 
					r[c[c_len].room_code].room_no= 30-fam_room; 
					fam_room--; 
					}
					c_len++;
					check_in(c, c_len);
				}
				break;
			case 5:
				exist=0;
				printf("---------------< Cancelation page >---------------\n");
				do{
					printf("Enter your Name : ");
					scanf("%s",temp);
					for(i=0; i<c_len;i++) {
						if(strcmp(c[i].name,temp) == 0) {exist=1; break;} 
					}
					if(exist ==0) printf("---< Person not Found >---\n");
				}while(exist==0);
				printf("Do you Wish to Cancel ( 1. Yes, 2. No ) : ");
				do{
				scanf("%d",&j);
				if(j == 1) { printf("\n---< Cancel Successful >---\n"); check_out(c,c_len,temp,i); c_len--;}
				else if(j == 2) printf("\n---< Cancel Unsuccessful >---\n");
				else printf("Wrong Input code entered, Enter Correct Code : ");
				}while((j != 1)&&(j != 2));	
				break;
			case 6: break;
			default: printf("-< Wrong Input Code Entered >-\n");
		}
	}while (input != 6);
	printf("\n-----< Thank You for Visiting Hotel Grand >-----");
}