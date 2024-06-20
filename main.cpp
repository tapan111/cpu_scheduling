#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <fstream>
#include <iostream>
#include <cstdlib>

class myapp : public cppcms::application {
public:
    myapp(cppcms::service &srv) : cppcms::application(srv) {}

    void upload() {
        if (request().request_method() == "POST") {
            auto file = request().files().get_file("file");
            if (file) {
                // Save the uploaded file
                std::string filename = file->filename();
                file->save_to("uploads/" + filename);

                // Run scheduler.cpp
                std::string command = "./scheduler uploads/" + filename;
                std::system(command.c_str());

                // Read the output from output.txt
                std::ifstream output_file("output.txt");
                std::string output((std::istreambuf_iterator<char>(output_file)),
                                    std::istreambuf_iterator<char>());

                // Display the output
                response().out() << "<html><body><pre>" << output << "</pre></body></html>";
                return;
            }
        }

        // Display file upload form
        response().out() <<
            "<html><body>"
            "<form method='post' enctype='multipart/form-data'>"
            "<input type='file' name='file' />"
            "<input type='submit' value='Upload' />"
            "</form>"
            "</body></html>";
    }
};

int main(int argc, char** argv) {
    try {
        cppcms::service srv(argc, argv);
        srv.applications_pool().mount(
            cppcms::applications_factory<myapp>()
        );
        srv.run();
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
}
