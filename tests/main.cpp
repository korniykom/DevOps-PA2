#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h> // JSON library to parse response

#define URL "http://127.0.0.1:8081/compute"

// This function is called by libcurl to write the received data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    strncat((char*)userp, (char*)contents, total_size);
    return total_size;
}

int main(void) {
    CURL *curl;
    CURLcode res;

    // Buffer to store the response data
    char response_data[1024] = {0};

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set CURL options
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_data);

        // Perform GET request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return 1;
        }

        // Print the received response (for debugging)
        printf("Response Data: %s\n", response_data);

        // Parse JSON response to extract elapsed time
        struct json_object *parsed_json;
        struct json_object *elapsed_time;

        parsed_json = json_tokener_parse(response_data);
        if (parsed_json == NULL) {
            fprintf(stderr, "Error parsing response as JSON\n");
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return 1;
        }

        // Extract the elapsed_time value
        if (json_object_object_get_ex(parsed_json, "elapsed_time", &elapsed_time)) {
            double time_in_ms = json_object_get_double(elapsed_time);
            printf("Elapsed Time: %.2f ms\n", time_in_ms);

            // Compare the elapsed time with 20000 ms
            if (time_in_ms < 20000) {
                // Test passed, return 0
                json_object_put(parsed_json);
                curl_easy_cleanup(curl);
                curl_global_cleanup();
                return 0;
            } else {
                // Test failed, return 1
                json_object_put(parsed_json);
                curl_easy_cleanup(curl);
                curl_global_cleanup();
                return 1;
            }
        } else {
            fprintf(stderr, "Failed to find 'elapsed_time' in response JSON\n");
            json_object_put(parsed_json);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return 1;
        }

        // Cleanup
        json_object_put(parsed_json);
        curl_easy_cleanup(curl);
    }

    // Cleanup global CURL resources
    curl_global_cleanup();

    return 1; // If something goes wrong, return 1 to indicate failure
}
