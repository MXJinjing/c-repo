 // long long p, q, front, rear, queue[10000];
    // front = 0, rear = 0, queue[0] = 0;
    // p = 0;
    // for (int i = 0; i < 26; i++)
    //     if (trie[p][i] != 0)
    //     {
    //         queue[front++] = trie[p][i];
    //         next[trie[p][i]] = 0;
    //     }

    // while (front > rear)
    // {
    //     p = queue[rear++];

    //     for (int i = 0; i < 26; i++)
    //         if (trie[p][i] != 0)
    //         {
    //             printf("fail[%lld] = %lld\n", trie[p][i], trie[next[p]][i]);
    //             queue[front++] = trie[p][i];
    //             next[trie[p][i]] = trie[next[p]][i];
    //         }
    //         else
    //         {
    //             printf("fail[%lld] = 0(root)\n", trie[p][i]);
    //             next[trie[p][i]] = 0;
    //         }
    // }