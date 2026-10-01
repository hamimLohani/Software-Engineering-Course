#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PAGES 200
#define MAX_FRAMES 50

typedef struct {
    int total_faults;
    int total_hits;
    double hit_ratio;
    double fault_ratio;
} SimStats;

// Helper function to check if a page is already present in any frame
int find_in_frames(const int frames[], int num_frames, int page) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return -1;
}

// Helper function to print frame header
void print_table_header(int num_frames) {
    printf("+-------+");
    for (int i = 0; i < num_frames; i++) {
        printf("---------+");
    }
    printf("----------+\n");

    printf("|  Ref  |");
    for (int i = 0; i < num_frames; i++) {
        printf(" Frame %-2d|", i + 1);
    }
    printf("  Status  |\n");

    printf("+-------+");
    for (int i = 0; i < num_frames; i++) {
        printf("---------+");
    }
    printf("----------+\n");
}

// Helper function to print a table row
void print_table_row(int page, const int frames[], int num_frames, bool is_hit) {
    printf("|  %3d  |", page);
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1) {
            printf("    -    |");
        } else {
            printf("   %3d   |", frames[i]);
        }
    }
    if (is_hit) {
        printf("   HIT    |\n");
    } else {
        printf("  FAULT   |\n");
    }
}

// Helper function to print table footer
void print_table_footer(int num_frames) {
    printf("+-------+");
    for (int i = 0; i < num_frames; i++) {
        printf("---------+");
    }
    printf("----------+\n");
}

// Helper to print summary statistics
void print_stats(const char *algo_name, SimStats stats, int total_pages) {
    printf("\n--- %s Summary ---\n", algo_name);
    printf("Total Page References: %d\n", total_pages);
    printf("Total Page Faults    : %d\n", stats.total_faults);
    printf("Total Page Hits      : %d\n", stats.total_hits);
    printf("Fault Ratio          : %.2f%%\n", stats.fault_ratio * 100.0);
    printf("Hit Ratio            : %.2f%%\n", stats.hit_ratio * 100.0);
}

// ==========================================
// 1. First-In, First-Out (FIFO)
// ==========================================
SimStats simulate_fifo(const int pages[], int n, int num_frames, bool verbose) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    int faults = 0;
    int hits = 0;
    int fifo_ptr = 0; // Pointer to the oldest frame slot

    if (verbose) {
        printf("\n========================================\n");
        printf("  FIFO (First-In, First-Out) Algorithm\n");
        printf("========================================\n");
        print_table_header(num_frames);
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pos = find_in_frames(frames, num_frames, page);
        bool is_hit = (pos != -1);

        if (is_hit) {
            hits++;
        } else {
            faults++;
            frames[fifo_ptr] = page;
            fifo_ptr = (fifo_ptr + 1) % num_frames;
        }

        if (verbose) {
            print_table_row(page, frames, num_frames, is_hit);
        }
    }

    if (verbose) {
        print_table_footer(num_frames);
    }

    SimStats stats;
    stats.total_faults = faults;
    stats.total_hits = hits;
    stats.hit_ratio = (double)hits / n;
    stats.fault_ratio = (double)faults / n;

    if (verbose) {
        print_stats("FIFO", stats, n);
    }
    return stats;
}

// ==========================================
// 2. Least Recently Used (LRU)
// ==========================================
SimStats simulate_lru(const int pages[], int n, int num_frames, bool verbose) {
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES]; // Tracks the reference index when each frame was last accessed

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int faults = 0;
    int hits = 0;

    if (verbose) {
        printf("\n========================================\n");
        printf("  LRU (Least Recently Used) Algorithm\n");
        printf("========================================\n");
        print_table_header(num_frames);
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pos = find_in_frames(frames, num_frames, page);
        bool is_hit = (pos != -1);

        if (is_hit) {
            hits++;
            last_used[pos] = i; // Update access timestamp
        } else {
            faults++;

            // Check if there is an empty frame first
            int empty_slot = -1;
            for (int f = 0; f < num_frames; f++) {
                if (frames[f] == -1) {
                    empty_slot = f;
                    break;
                }
            }

            if (empty_slot != -1) {
                frames[empty_slot] = page;
                last_used[empty_slot] = i;
            } else {
                // Find the frame with the minimum last_used value
                int lru_index = 0;
                int min_time = last_used[0];
                for (int f = 1; f < num_frames; f++) {
                    if (last_used[f] < min_time) {
                        min_time = last_used[f];
                        lru_index = f;
                    }
                }
                frames[lru_index] = page;
                last_used[lru_index] = i;
            }
        }

        if (verbose) {
            print_table_row(page, frames, num_frames, is_hit);
        }
    }

    if (verbose) {
        print_table_footer(num_frames);
    }

    SimStats stats;
    stats.total_faults = faults;
    stats.total_hits = hits;
    stats.hit_ratio = (double)hits / n;
    stats.fault_ratio = (double)faults / n;

    if (verbose) {
        print_stats("LRU", stats, n);
    }
    return stats;
}

// ==========================================
// 3. Optimal (OPT / Belady's Optimal)
// ==========================================
SimStats simulate_optimal(const int pages[], int n, int num_frames, bool verbose) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    int faults = 0;
    int hits = 0;

    if (verbose) {
        printf("\n========================================\n");
        printf("  Optimal (OPT) Page Replacement\n");
        printf("========================================\n");
        print_table_header(num_frames);
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pos = find_in_frames(frames, num_frames, page);
        bool is_hit = (pos != -1);

        if (is_hit) {
            hits++;
        } else {
            faults++;

            // Check if there is an empty frame first
            int empty_slot = -1;
            for (int f = 0; f < num_frames; f++) {
                if (frames[f] == -1) {
                    empty_slot = f;
                    break;
                }
            }

            if (empty_slot != -1) {
                frames[empty_slot] = page;
            } else {
                // Find page in frames that will not be used for longest time in the future
                int victim_frame = -1;
                int farthest_next_use = -1;

                for (int f = 0; f < num_frames; f++) {
                    int next_use = -1;
                    for (int j = i + 1; j < n; j++) {
                        if (pages[j] == frames[f]) {
                            next_use = j;
                            break;
                        }
                    }

                    // If a frame's page is never referenced again in the future
                    if (next_use == -1) {
                        victim_frame = f;
                        break;
                    }

                    if (next_use > farthest_next_use) {
                        farthest_next_use = next_use;
                        victim_frame = f;
                    }
                }

                frames[victim_frame] = page;
            }
        }

        if (verbose) {
            print_table_row(page, frames, num_frames, is_hit);
        }
    }

    if (verbose) {
        print_table_footer(num_frames);
    }

    SimStats stats;
    stats.total_faults = faults;
    stats.total_hits = hits;
    stats.hit_ratio = (double)hits / n;
    stats.fault_ratio = (double)faults / n;

    if (verbose) {
        print_stats("Optimal", stats, n);
    }
    return stats;
}

// Comparison table for all 3 algorithms
void print_comparison_table(SimStats fifo, SimStats lru, SimStats opt, int total_pages) {
    printf("\n\n========================================================================\n");
    printf("                  ALGORITHM COMPARISON SUMMARY                          \n");
    printf("========================================================================\n");
    printf("+------------+--------------+--------------+-------------+-------------+\n");
    printf("| Algorithm  | Total Pages  | Page Faults  | Page Hits   | Hit Ratio   |\n");
    printf("+------------+--------------+--------------+-------------+-------------+\n");
    printf("| FIFO       | %12d | %12d | %11d | %10.2f%% |\n", total_pages, fifo.total_faults, fifo.total_hits, fifo.hit_ratio * 100.0);
    printf("| LRU        | %12d | %12d | %11d | %10.2f%% |\n", total_pages, lru.total_faults, lru.total_hits, lru.hit_ratio * 100.0);
    printf("| Optimal    | %12d | %12d | %11d | %10.2f%% |\n", total_pages, opt.total_faults, opt.total_hits, opt.hit_ratio * 100.0);
    printf("+------------+--------------+--------------+-------------+-------------+\n");
}

int main(void) {
    int choice;
    int num_frames = 3;
    int num_pages = 20;

    // Standard textbook reference string (Galvin OS Concepts)
    int pages[MAX_PAGES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

    printf("====================================================\n");
    printf("       PAGE REPLACEMENT ALGORITHM SIMULATOR (C)     \n");
    printf("====================================================\n");
    printf("Choose input mode:\n");
    printf("  1. Use Standard Demo Reference String (20 pages, 3 frames)\n");
    printf("  2. Enter Custom Reference String and Frames\n");
    printf("Enter choice (1 or 2): ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    if (choice == 2) {
        printf("\nEnter number of frames (e.g. 3): ");
        if (scanf("%d", &num_frames) != 1 || num_frames <= 0 || num_frames > MAX_FRAMES) {
            printf("Invalid frame count. Must be between 1 and %d.\n", MAX_FRAMES);
            return 1;
        }

        printf("Enter number of page references (e.g. 20): ");
        if (scanf("%d", &num_pages) != 1 || num_pages <= 0 || num_pages > MAX_PAGES) {
            printf("Invalid page count. Must be between 1 and %d.\n", MAX_PAGES);
            return 1;
        }

        printf("Enter the %d page references separated by space:\n", num_pages);
        for (int i = 0; i < num_pages; i++) {
            if (scanf("%d", &pages[i]) != 1) {
                printf("Error reading page reference #%d.\n", i + 1);
                return 1;
            }
        }
    }

    printf("\n--- Simulation Parameters ---\n");
    printf("Number of Frames: %d\n", num_frames);
    printf("Reference String: ");
    for (int i = 0; i < num_pages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    // Run all 3 algorithms with detailed trace
    SimStats fifo_stats = simulate_fifo(pages, num_pages, num_frames, true);
    SimStats lru_stats = simulate_lru(pages, num_pages, num_frames, true);
    SimStats opt_stats = simulate_optimal(pages, num_pages, num_frames, true);

    // Print side-by-side comparison summary
    print_comparison_table(fifo_stats, lru_stats, opt_stats, num_pages);

    return 0;
}
