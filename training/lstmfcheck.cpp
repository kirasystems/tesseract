///////////////////////////////////////////////////////////////////////
// File:        lstmcheck.cpp
// Description: Checks the validity of lstmf files.
// Author:      Alexander Hudek
// Created:     April 16, 2018
//
// (C) Copyright 2018, Kira Inc.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
///////////////////////////////////////////////////////////////////////

#ifdef GOOGLE_TESSERACT
#include "base/commandlineflags.h"
#endif
#include "commontraining.h"
#include "genericvector.h"
#include "imagedata.h"
#include "strngs.h"
#include "tprintf.h"

STRING_PARAM_FLAG(eval_listfile, "",
                  "File listing sample files in lstmf training format.");
INT_PARAM_FLAG(verbosity, 1,
               "Amount of diagnosting information to output (0-2).");

int main(int argc, char **argv) {
  using namespace tesseract;
  ParseArguments(&argc, &argv);
  if (FLAGS_eval_listfile.empty()) {
    tprintf("Must provide a --eval_listfile!\n");
    return 1;
  }

  GenericVector<STRING> filenames;
  if (!LoadFileLinesToStrings(FLAGS_eval_listfile.c_str(), &filenames)) {
    tprintf("Failed to load list of eval filenames from %s\n",
            FLAGS_eval_listfile.c_str());
    return 1;
  }

  for (int i = 0; i < filenames.size(); ++i) {
      tprintf("Checking %s\n", filenames[i].c_str());
      DocumentData doc("test");
      if (!doc.LoadDocument(filenames[i].c_str(), 0, 0, nullptr)) {
        tprintf("FAILED: %s\n", filenames[i].c_str());
      }
  }
  return 0;
} /* main */
