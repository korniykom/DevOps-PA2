#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Callback function for handling received data from libcurl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    strncat((char*)userp, (char*)contents, total_size);
    return total_size;
}

int main(void) {
    CURL *curl;
    CURLcode res;

    // Buffer to store the response data
    char response_data[256] = {0};  // Assuming the response will be small enough to fit here

    // Initialize libcurl globally
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/calculate");

        // Set the callback function to handle the response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_data);

        // Perform the GET request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return 1;  // Return 1 indicating failure
        }

        // Convert response data to an integer
        int elapsed_time = atoi(response_data);  // Convert response to an integer

        // Print the response value for debugging
        printf("Elapsed Time: %d\n", elapsed_time);

        // Compare the response value to 20000
        if (elapsed_time < 20000) {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return 0;  // Return 0 indicating success (elapsed time < 20000)
        } else {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return 1;  // Return 1 indicating failure (elapsed time >= 20000)
        }
    }

    // Cleanup global CURL resources if curl_easy_init fails
    curl_global_cleanup();
    return 1;  // Return 1 to indicate something went wrong
}
