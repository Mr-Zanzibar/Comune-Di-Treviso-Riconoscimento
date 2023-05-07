#include <iostream>
#include <ctime>
#include <openssl/pem.h>
#include <openssl/evp.h>

int main()
{
    while (true) {
        // Imposta la data corrente
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        int current_year = now->tm_year + 1900;
        int current_month = now->tm_mon + 1;
        int current_day = now->tm_mday;

        // Imposta la data di scadenza del documento, ogni tesserino di riconoscimento per la sede del comune di treviso scade il 31/12/2025
        int expiry_year = 2025;
        int expiry_month = 12;
        int expiry_day = 31;

        // Verifica se il documento è scaduto
        bool is_expired = (current_year > expiry_year) ||
                          (current_year == expiry_year && current_month > expiry_month) ||
                          (current_year == expiry_year && current_month == expiry_month && current_day > expiry_day);

        if (is_expired)
        {
            std::cout << "Il documento è scaduto." << std::endl;
        }
        else
        {
            std::cout << "Il documento è valido." << std::endl;
        }

        // Verifica l'autenticità della firma digitale
        OpenSSL_add_all_algorithms();
        ERR_load_BIO_strings();
        ERR_load_crypto_strings();

        const char* signature_data = "Q2FsdGVkX1+5y5iDpiJbKPZ9X9U0/LJ6UQX6q3c6jKysfZPllRmGChmBJlKyTGGv\nnVpTeu+TJgXaF+/iICUE8V7TrnISl4/qV05UHk6ya8ki6UZOin6xtqX6ZtbBvZ8W\nwRwRpe1BpJQUzvId8oFkAHoyVyIfDYuw9xd5cZ/LmWlP2Cm3q+dEGM2oAJjjmqYz\nPHhFCgO9rclxxZ+1SWZ+zSYE0G98xYZgcy+HlLYt7Yg1vjBlrJhXfZ+xy/E1pWZO\nnLxh/wfcyJYSv8D5+tyfRJjdGE9E5mp5cMTC5rmJ2Lh5x5q1JvK8UzmsXCQ6BqU6\nLmJZEMBBscWcwwRfR1p18uToUKz8N7VcF36I9S47Xng=";
        const char* public_key_data = "-----BEGIN PUBLIC KEY-----\nMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEArcs7Ua3/tkCQ2ALiMvU8\nBRp23LRbRdpfKZuHvU8WSEp5B1fRd9Nyblzohqq8Bjw15qktOefDQl5OZj5W5t/9\nr9cm";

        BIO* bio = BIO_new_mem_buf((void*)public_key_data, -1);
        EVP_PKEY* pubkey = PEM_read_bio
        time_t now = time(nullptr);
        struct tm* timeinfo = localtime(&now);
        char date_str[11];
        strftime(date_str, sizeof(date_str), "%d/%m/%Y", timeinfo);

        // Verifica se il documento è scaduto
        if (expiry_date < date_str) {
            std::cout << "Il documento è scaduto." << std::endl;
        } else {
            std::cout << "Il documento è valido." << std::endl;
        }

        // Verifica l'autenticità della firma digitale
        EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
        if (!md_ctx) {
            std::cerr << "Errore durante l'inizializzazione del contesto di hash." << std::endl;
            return 1;
        }

        if (EVP_VerifyInit(md_ctx, EVP_sha256()) != 1) {
            std::cerr << "Errore durante l'inizializzazione dell'algoritmo di hash." << std::endl;
            return 1;
        }

        if (EVP_VerifyUpdate(md_ctx, doc_data, doc_len) != 1) {
            std::cerr << "Errore durante l'aggiornamento dell'hash con i dati del documento." << std::endl;
            return 1;
        }

        if (EVP_VerifyFinal(md_ctx, signature_data, signature_len, pubkey) != 1) {
            std::cerr << "La firma digitale del documento non è autentica." << std::endl;
            return 1;
        }

        std::cout << "La firma digitale del documento è autentica." << std::endl;

        // Rilascia le risorse
        EVP_PKEY_free(pubkey);
        BIO_free_all(pubkey_bio);
        EVP_MD_CTX_free(md_ctx);

        // Attendi un giorno prima di verificare il documento successivo
        sleep(86400);
    }

    return 0;
}
