#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct line {
    int tag;
    int last_used_time;
};

typedef struct line* set;

set* cache;

int v = 0, s, b, E, time_stamp = 0;
unsigned hits = 0, misses = 0, evictions = 0;

// 打印使用说明
void printHelp() {
    puts("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>");
    puts("Options:");
    puts("  -h         Print this help message.");
    puts("  -v         Optional verbose flag.");
    puts("  -s <num>   Number of set index bits.");
    puts("  -E <num>   Number of lines per set.");
    puts("  -b <num>   Number of block offset bits.");
    puts("  -t <file>  Trace file.");
    puts("");
    puts("Examples:");
    puts("  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace");
    puts("  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace");
}

// 获取输入参数，返回文件指针
FILE* getArg(int argc, char *argv[]) {
    FILE *trace_file;
    int opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch(opt) {
            case 'h':
                printHelp();
                exit(0);
            case 'v':
                v = 1;
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                trace_file = fopen(optarg, "r");
                break;
            default:
                printHelp();
                exit(1);
        }
    }
    return trace_file;
}

// 初始化缓存
void initCache() {
    int S = 1 << s;
    cache = (set*)malloc(sizeof(set) * S);
    for (int i = 0; i < S; ++i) {
        cache[i] = (set)malloc(sizeof(struct line) * E);
        for (int j = 0; j < E; ++j) {
            cache[i][j].tag = -1;
            cache[i][j].last_used_time = -1;
        }
    }
}

// 使用缓存
void useCache(size_t addr, int is_modify) {
    int set_pos = addr >> b & ((1 << s) - 1);
    int tag = addr >> (s + b);

    set cur_set = cache[set_pos];
    int lru_ops = 0, lru_time = cur_set[0].last_used_time;

    for (int i = 0; i < E; ++i) {
        if (cur_set[i].tag == tag) {
            ++hits;
            hits += is_modify;
            cur_set[i].last_used_time = time_stamp;
            if (v) {
                printf("hit\n");
            }
            return;
        }

        // 寻找使用时间最早的缓冲行，作为驱逐的对象
        if (cur_set[i].last_used_time < lru_time) {
            lru_time = cur_set[i].last_used_time;
            lru_ops = i;
        }
    }

    // 没有命中
    ++misses;
    // 如果是修改操作，那么其中的写操作一定命中
    hits += is_modify;

    // 冷不命中
    evictions += (lru_time != -1);

    if (v) {
        if (lru_time != -1) {
            if (is_modify)
                printf("miss eviction hit\n");
            else
                printf("miss eviction\n");
        } else
            printf("miss\n");
    }

    // 驱逐
    cur_set[lru_ops].last_used_time = time_stamp;
    cur_set[lru_ops].tag = tag;
    return;
}

int main(int argc, char *argv[]) {
    FILE *trace_file = getArg(argc, argv);
    initCache();

    int size;
    size_t addr;
    char operation;
    
    // 必须是%s，因为开头有可能是空白符
    while (fscanf(trace_file, "%s %lx,%d\n", &operation, &addr, &size) == 3) {
        time_stamp++;
        if (v) {
            printf("%c %lx,%d ", operation, addr, size);
        }
        switch(operation) {
            case 'I':
                continue;
            case 'M':
                useCache(addr, 1);
                break;
            case 'L':
            case 'S':
                useCache(addr, 0);
        }
    }

    free(cache);
    printSummary(hits, misses, evictions);
    return 0;
}