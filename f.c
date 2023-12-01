#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int tile_amt;
    char round_id[37];
} Interaction;

typedef struct {
    int index;
    char value;
} GridTile;

typedef struct {
    int synced;
    char user[256]; // Assuming the maximum length of user is 255 characters
} DiscordClient;

void wait_until_ready(DiscordClient* client) {
    // Simulate waiting until the bot is ready
}

void sync(DiscordClient* client) {
    // Simulate syncing
    client->synced = 1;
}

void on_ready(DiscordClient* client) {
    wait_until_ready(client);
    if (!client->synced) {
        sync(client);
    }
    printf("We have logged in as %s.\n", client->user);
}

void send_message(char* content) {
    // Simulate sending a message
    printf("%s\n", content);
}

void mines(Interaction* interaction) {
    if (strlen(interaction->round_id) == 36) {
        time_t start_time = time(NULL);

        GridTile grid[25];
        for (int i = 0; i < 25; i++) {
            grid[i].index = i;
            grid[i].value = '❌';
        }

        int already_used[25];
        int count = 0;

        while (interaction->tile_amt > count) {
            int a = rand() % 25;
            int found = 0;

            for (int i = 0; i < count; i++) {
                if (already_used[i] == a) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                continue;
            }

            already_used[count] = a;
            grid[a].value = '✅';
            count++;
        }

        int chance = rand() % 51 + 45;
        if (interaction->tile_amt < 4) {
            chance = chance - 15;
        }

        printf("Grid:\n");
        for (int i = 0; i < 25; i++) {
            printf("%c", grid[i].value);
            if (i % 5 == 4) {
                printf("\n");
            }
        }

        printf("\nAccuracy: %d%%\nRound ID: %s\nResponse Time: %ld seconds\n", chance, interaction->round_id, time(NULL) - start_time);
    } else {
        printf("Error: Invalid round id\n");
    }
}

int main() {
    DiscordClient client;
    Interaction interaction;
    strcpy(client.user, "Bot User"); // Replace with your actual bot username
    client.synced = 0;
    interaction.tile_amt = 5; // Replace with your actual tile_amt value
    strcpy(interaction.round_id, "123456789012345678901234567890123456"); // Replace with your actual round_id value

    on_ready(&client);
    mines(&interaction);

    return 0;
}
