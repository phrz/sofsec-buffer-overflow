// -std=c99 -fno-stack-protector

#include <stdio.h>
#include <string.h>
#define B_SIZE 16
#define N_USERS 5
#define N_TRANSACTIONS 25

struct User { char username[B_SIZE], password[B_SIZE], name[B_SIZE]; };
struct User users[N_USERS];

struct Transaction { int user_id, amount_cents; char vendor[B_SIZE]; };
struct Transaction transactions[N_TRANSACTIONS];

void authenticate(int* user_id, char* username, char* password, int* is_admin);
void display_transactions(int user_id, int is_admin);
int strings_equal(char const* a, char const* b);

int main() {
	int user_id = -1;
	unsigned is_admin = 0;
	char password[B_SIZE];
	char username[B_SIZE];	
	
	puts("Welcome to Riverbanks Credit Union");
	
	// Log in process
	authenticate(&user_id, &username[0], &password[0], &is_admin);
	
	// Authenticated
	printf("\nWelcome, %s!\n", users[user_id].name);
	
	// Display transactions
	display_transactions(user_id, is_admin);
}

// Log the user in (set the user_id variable when authenticated)
void authenticate(int* user_id, char* username, char* password, int* is_admin) {
	while(1) {
		puts("==================================");
		printf("Username: ");
		fscanf(stdin, "%s", username);
		printf("Password: ");
		fscanf(stdin, "%s", password);
		
		for(int i = 0; i < N_USERS; i++) {
			int user_compare = strings_equal(username, users[i].username);
			int pass_compare = strings_equal(password, users[i].password);
			if(user_compare && pass_compare) {
				*user_id = i;
				break;
			}
		}
		if(*user_id != -1) {
			break;
		} else {
			puts("Please check your username and password.");
		}
	}
}

// Print the user's transactions, or all transactions if admin.
void display_transactions(int user_id, int is_admin) {
	if(is_admin) {
		puts("\n*ADMIN MODE: VIEWING ALL TRANSACTIONS*");
	}
	printf("\n%-16s | %-8s | %s\n", "User", "Cost", "Vendor");
	puts("———————————————————————————————————————————————");
	for(int i = 0; i < N_TRANSACTIONS; i++) {
		if(is_admin || user_id == transactions[i].user_id) {
			char* name = users[transactions[i].user_id].name;
			double cost = (double)transactions[i].amount_cents / 100.;
			char* vendor = transactions[i].vendor;
			printf("%-16s | %8.2f | %s\n", name, cost, vendor);
		}
	}
}

// A safer alternative to strcmp: stop comparing strings
// when one runs out.
int strings_equal(char const* a, char const* b) {
	// 0 is false: different or error
	// 1 is true: same strings
	if(!a || !b) {
		return 0;
	}
	size_t i = 0;
	while(a[i] != '\0' && b[i] != '\0') {
		if(a[i] != b[i]) {
			return 0;
		}
		i++;
	}
	return 1;
}

/* ============================================ *
 *  The "database" (hidden from users)          *
 * ============================================ */

struct User users[N_USERS] = {
	// user     pass        name
	{  "john",  "123456",   "John Appleseed" },
	{  "mia",   "password", "Mia Schultz"    },
	{  "ali",   "welcome",  "Ali Khoury"     },
	{  "davi",  "ninja",    "Davi Silva"     },
	{  "pilar", "abc123",   "Pilar Markel"   },
};

struct Transaction transactions[N_TRANSACTIONS] = {
	// user id   cents   vendor
	{  0,        45677,  "Innojam"      },
	{  0,        9978,   "Vimbo"        },
	{  0,        32766,  "Fivespan"     },
	{  0,        2256,   "Thoughtstorm" },
	{  0,        22106,  "Jabbertype"   },
	
	{  1,        23840,  "Skynoodle"    },
	{  1,        11638,  "Zoomzone"     },
	{  1,        2839,   "Gabspot"      },
	{  1,        34516,  "Voonte"       },
	{  1,        43963,  "Meeveo"       },
	
	{  2,        44764,  "Thoughtblab"  },
	{  2,        12012,  "Oloo"         },
	{  2,        48256,  "Brainsphere"  },
	{  2,        33962,  "Vinte"        },
	{  2,        29281,  "Skyvu"        },
	
	{  3,        15105,  "Photolist"    },
	{  3,        10906,  "Jetwire"      },
	{  3,        49119,  "Babblestorm"  },
	{  3,        12757,  "Oyoyo"        },
	{  3,        21512,  "Layo"         },
	
	{  4,        9322,   "Jetpulse"     },
	{  4,        49052,  "Geevee"       },
	{  4,        10815,  "Quaxo"        },
	{  4,        27701,  "Abatz"        },
	{  4,        5795,   "Photobug"     },
};
