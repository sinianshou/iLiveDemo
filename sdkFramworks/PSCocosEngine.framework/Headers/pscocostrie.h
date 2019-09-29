//
//  pscocostrie.h
//  PSCocosEngine
//
//  Created by swj-macbook on 2018/11/26.
//  Copyright © 2018 sjdd. All rights reserved.
//

#ifndef pscocostrie_h
#define pscocostrie_h

#include "pscocos_macro.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    int children[200][256];
    int index[200];
    int size;
} PSCOCOSTRIE;

int pscocos_trie_init(PSCOCOSTRIE *trie);
int pscocos_trie_find(PSCOCOSTRIE *trie, const char* key, int len);
const char* pscocos_trie_getConstKey(int index);
    
int pscocos_trie_getConstKeyLen(int index);
    
#ifdef __cplusplus
}
#endif


#endif /* pscocostrie_hpp */
