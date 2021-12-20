#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include "../include/config.hpp"
#include "../include/head.hpp"
#include "../include/page.hpp"
#include "../include/category.hpp"
#include "../include/home.hpp"
#include "../include/template.hpp"

using namespace std;

void createSite(string filename, string path)
{
  std::filesystem::path site_path{path.data()};
  if (!std::filesystem::exists(site_path))
  {
    std::filesystem::create_directory(site_path);
  }

  Category *Categories[16];

  Config *conf = configParser();
  TemplateManager TemplateMgr(conf->templatefile);
  Category **cats;
  int categoryCount = 0;
  cats = createCategories(Categories, &categoryCount, filename, path, &TemplateMgr);

  // Debug categories
  cout << "\nCategories found: " << categoryCount << endl;
  // printContent(cats,categoryCount);

  buildHome(conf, cats, categoryCount, path);
  for (int i = 0; i <= categoryCount; i++)
  { // Build all pages including seperate pages
    Category tempCat = *cats[i];

    for (int pageno = 0; pageno < tempCat.pageCount; pageno++)
    {
      Page *tempPage = tempCat.pages[pageno];
      buildPage(conf, tempPage, path);
    }
  }
}
