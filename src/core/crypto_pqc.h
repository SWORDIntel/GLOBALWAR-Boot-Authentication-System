/*
 * GLOBALWAR Quantum-Safe Cryptography Header
 *
 * NIST-Standardized Post-Quantum Cryptography:
 * - ML-KEM-1024 (FIPS 203) - Module-Lattice Key Encapsulation
 * - ML-DSA-87 (FIPS 204) - Module-Lattice Digital Signature Algorithm
 * - AES-256-GCM - Authenticated Encryption
 */

#ifndef CRYPTO_PQC_H
#define CRYPTO_PQC_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Algorithm parameter sizes (NIST standards)
#define ML_KEM_1024_PUBLIC_KEY_BYTES    1568
#define ML_KEM_1024_SECRET_KEY_BYTES    3168
#define ML_KEM_1024_CIPHERTEXT_BYTES    1568
#define ML_KEM_1024_SHARED_SECRET_BYTES 32

#define ML_DSA_87_PUBLIC_KEY_BYTES      2592
#define ML_DSA_87_SECRET_KEY_BYTES      4896
#define ML_DSA_87_SIGNATURE_BYTES       4627

#define AES_256_KEY_BYTES               32
#define AES_256_GCM_IV_BYTES            12
#define AES_256_GCM_TAG_BYTES           16

/*
 * System Initialization
 */

// Initialize crypto system
// simulation_mode: if true, uses placeholder crypto (for testing)
bool init_crypto_system(bool simulation_mode);

// Clean up and zero sensitive data
void cleanup_crypto_system();

// Log current cryptographic state
void log_crypto_state();

/*
 * ML-KEM-1024 Functions (FIPS 203)
 */

// Generate ML-KEM-1024 keypair
bool ml_kem_1024_keypair(uint8_t* public_key, uint8_t* secret_key);

// Encapsulate to create shared secret
bool ml_kem_1024_encapsulate(const uint8_t* public_key,
                              uint8_t* ciphertext,
                              uint8_t* shared_secret);

// Decapsulate to recover shared secret
bool ml_kem_1024_decapsulate(const uint8_t* secret_key,
                              const uint8_t* ciphertext,
                              uint8_t* shared_secret);

/*
 * ML-DSA-87 Functions (FIPS 204)
 */

// Generate ML-DSA-87 keypair
bool ml_dsa_87_keypair(uint8_t* public_key, uint8_t* secret_key);

// Sign a message
bool ml_dsa_87_sign(const uint8_t* secret_key,
                    const uint8_t* message,
                    size_t message_len,
                    uint8_t* signature,
                    size_t* signature_len);

// Verify a signature
bool ml_dsa_87_verify(const uint8_t* public_key,
                      const uint8_t* message,
                      size_t message_len,
                      const uint8_t* signature,
                      size_t signature_len);

/*
 * AES-256-GCM Functions
 */

// Encrypt with authenticated encryption
bool aes_256_gcm_encrypt(const uint8_t* key,
                         const uint8_t* iv,
                         const uint8_t* plaintext,
                         size_t plaintext_len,
                         const uint8_t* aad,      // Additional authenticated data
                         size_t aad_len,
                         uint8_t* ciphertext,
                         uint8_t* tag);

// Decrypt and verify
bool aes_256_gcm_decrypt(const uint8_t* key,
                         const uint8_t* iv,
                         const uint8_t* ciphertext,
                         size_t ciphertext_len,
                         const uint8_t* aad,
                         size_t aad_len,
                         const uint8_t* tag,
                         uint8_t* plaintext);

/*
 * High-Level Application Functions
 */

// Sign boot measurements for integrity verification
bool sign_boot_measurement(const uint8_t* measurement,
                           size_t measurement_len,
                           uint8_t* signature,
                           size_t* signature_len);

// Verify boot measurement signature
bool verify_boot_measurement(const uint8_t* measurement,
                             size_t measurement_len,
                             const uint8_t* signature,
                             size_t signature_len);

// Encrypt passphrase for secure storage
bool encrypt_passphrase(const char* passphrase,
                        uint8_t* ciphertext,
                        size_t* ciphertext_len,
                        uint8_t* iv,
                        uint8_t* tag);

// Decrypt passphrase from secure storage
bool decrypt_passphrase(const uint8_t* ciphertext,
                        size_t ciphertext_len,
                        const uint8_t* iv,
                        const uint8_t* tag,
                        char* passphrase,
                        size_t passphrase_buffer_len);

#endif // CRYPTO_PQC_H
