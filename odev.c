#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* yeniDugum(int deger) {
    Node* dugum = (Node*)malloc(sizeof(Node));
    dugum->data = deger;
    dugum->left = NULL;
    dugum->right = NULL;
    return dugum;
}

Node* ekle(Node* kok, int deger) {
    if (kok == NULL) {
        return yeniDugum(deger);
    }
    if (deger < kok->data) {
        kok->left = ekle(kok->left, deger);
    } else if (deger > kok->data) {
        kok->right = ekle(kok->right, deger);
    }
    return kok;
}

int hazineAra(Node* kok, int aranan, int* adimSayisi) {
    if (kok == NULL) {
        return 0; 
    }

    (*adimSayisi)++;
    printf("%d. Adim -> Ziyaret edilen dugum: %d\n", *adimSayisi, kok->data);

    if (kok->data == aranan) {
        return 1; 
    }

    if (aranan < kok->data) {
        return hazineAra(kok->left, aranan, adimSayisi);
    } else {
        return hazineAra(kok->right, aranan, adimSayisi);
    }
}

int agacYuksekligi(Node* kok) {
    if (kok == NULL) {
        return 0;
    }
    
    int solYukseklik = agacYuksekligi(kok->left);
    int sagYukseklik = agacYuksekligi(kok->right);

    if (solYukseklik > sagYukseklik) {
        return solYukseklik + 1;
    } else {
        return sagYukseklik + 1;
    }
}

void bellegiTemizle(Node* kok) {
    if (kok == NULL) return;
    bellegiTemizle(kok->left);
    bellegiTemizle(kok->right);
    free(kok);
}

int main() {
    Node* kok = NULL;

    int hazineler[] = {10, 5, 15, 3, 7, 12, 18, 20};
    int elemanSayisi = sizeof(hazineler) / sizeof(hazineler[0]);

    for (int i = 0; i < elemanSayisi; i++) {
        kok = ekle(kok, hazineler[i]);
    }

    int enKotuDurum = agacYuksekligi(kok);
    int arananSayi;

    printf("=== HAZINE AGACI OYUNU ===\n");
    printf("Ipucu: Hazineler 1 ile 20 arasindaki sayilarda gizli!\n");
    printf("Agacin toplam derinligi (En kotu durumda gereken maksimum adim): %d\n", enKotuDurum);

    while (1) {
        printf("\nKazmak istediginiz sayiyi girin (Cikis icin 0): ");
        scanf("%d", &arananSayi);

        if (arananSayi == 0) {
            printf("Oyundan cikiliyor...\n");
            break;
        }

        int harcananAdim = 0;
        printf("\n--- Arama Adimlari ---\n");
        int sonuc = hazineAra(kok, arananSayi, &harcananAdim);

        printf("\n--- Sonuc ---\n");
        if (sonuc == 1) {
            printf("Hazine bulundu! (Toplam %d adimda buldun)\n", harcananAdim);
        } else {
            printf("Bosuna kazdin! (%d adim aradin ama cikmadi)\n", harcananAdim);
        }
    }

    bellegiTemizle(kok);
    return 0;
}