/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <gtest/gtest.h>
#include <string>

#include <ignition/common/Console.hh>

#include "ignition/fuel_tools/ClientConfig.hh"
#include "ignition/fuel_tools/ModelIdentifier.hh"

using namespace ignition;
using namespace fuel_tools;

/////////////////////////////////////////////////
/// \brief Fields can be set
TEST(ModelIdentifier, SetFields)
{
  ModelIdentifier id;
  id.SetName("hello");
  id.SetUuid("lllooo000ooolll");
  id.SetFileSize(2048u);
  std::time_t d1;
  std::time(&d1);
  id.SetModifyDate(d1);
  std::time_t d2;
  std::time(&d2);
  id.SetUploadDate(d2);

  EXPECT_EQ(std::string("hello"), id.Name());
  EXPECT_EQ(std::string("lllooo000ooolll"), id.Uuid());
  EXPECT_EQ(2048u, id.FileSize());
  EXPECT_EQ(d1, id.ModifyDate());
  EXPECT_EQ(d2, id.UploadDate());
}

/////////////////////////////////////////////////
/// \brief Unique Name
TEST(ModelIdentifier, UniqueName)
{
  ignition::fuel_tools::ServerConfig srv1;
  srv1.SetUrl("http://localhost:8001/");

  ignition::fuel_tools::ServerConfig srv2;
  srv1.SetUrl("http://localhost:8001");

  ignition::fuel_tools::ServerConfig srv3;
  srv1.SetUrl("https://localhost:8001//////////////////////////");

  ModelIdentifier id;
  id.SetName("hello");
  id.SetOwner("alice");
  id.SetServer(srv1);
  EXPECT_EQ("https://localhost:8001/1.0/alice/models/hello", id.UniqueName());

  id.SetServer(srv2);
  EXPECT_EQ("https://localhost:8001/1.0/alice/models/hello", id.UniqueName());

  id.SetServer(srv3);
  EXPECT_EQ("https://localhost:8001/1.0/alice/models/hello", id.UniqueName());
}

/////////////////////////////////////////////////
/// \brief Copy constructor deep copies
TEST(ModelIdentifier, CopyConstructorDeepCopy)
{
  ModelIdentifier id;
  id.SetName("hello");
  id.SetUuid("lllooo000ooolll");
  id.SetFileSize(2048u);
  std::time_t d1;
  std::time(&d1);
  id.SetModifyDate(d1);
  std::time_t d2;
  std::time(&d2);
  id.SetUploadDate(d2);

  ModelIdentifier id2(id);
  EXPECT_EQ(std::string("hello"), id2.Name());
  EXPECT_EQ(std::string("lllooo000ooolll"), id2.Uuid());
  EXPECT_EQ(2048u, id2.FileSize());
  EXPECT_EQ(d1, id2.ModifyDate());
  EXPECT_EQ(d2, id2.UploadDate());

  id2.SetName("hello2");
  EXPECT_EQ(std::string("hello"), id.Name());
  EXPECT_EQ(std::string("hello2"), id2.Name());
}

/////////////////////////////////////////////////
/// \brief assignment operator deep copies
TEST(ModelIdentifier, AssignmentOperatorDeepCopy)
{
  ModelIdentifier id;
  id.SetName("hello");
  id.SetUuid("lllooo000ooolll");
  id.SetFileSize(2048u);
  std::time_t d1;
  std::time(&d1);
  id.SetModifyDate(d1);
  std::time_t d2;
  std::time(&d2);
  id.SetUploadDate(d2);

  ModelIdentifier id2(id);
  id2 = id;
  EXPECT_EQ(std::string("hello"), id2.Name());
  EXPECT_EQ(std::string("lllooo000ooolll"), id2.Uuid());
  EXPECT_EQ(2048u, id2.FileSize());
  EXPECT_EQ(d1, id2.ModifyDate());
  EXPECT_EQ(d2, id2.UploadDate());


  id2.SetName("hello2");
  EXPECT_EQ(std::string("hello"), id.Name());
  EXPECT_EQ(std::string("hello2"), id2.Name());
}

/////////////////////////////////////////////////
TEST(ModelIdentifier, AsString)
{
  common::Console::SetVerbosity(4);
  {
    ModelIdentifier id;
    std::string str =
        "Name: \n"\
        "Owner: \n"\
        "Unique name: /1.0//models/\n"
        "Description: \n"
        "File size: 0\n"
        "Upload date: 0\n"
        "UUID: \n"
        "Likes: 0\n"
        "Downloads: 0\n"
        "License name: \n"
        "License URL: \n"
        "License image URL: \n"
        "Tags: \n"
        "Server:\n"
        "  URL: \n"
        "  Version: 1.0\n"
        "  API key: \n";
    EXPECT_EQ(str, id.AsString());
  }

  {
    ModelIdentifier id;
    id.SetName("hello");
    id.SetUuid("lllooo000ooolll");
    id.SetFileSize(2048u);
    std::time_t d1;
    std::time(&d1);
    id.SetModifyDate(d1);
    std::time_t d2;
    std::time(&d2);
    id.SetUploadDate(d2);

    auto str = id.AsString();
    igndbg << str << std::endl;

    EXPECT_NE(str.find("hello"), std::string::npos);
    EXPECT_NE(str.find("lllooo000ooolll"), std::string::npos);
    EXPECT_NE(str.find("2048"), std::string::npos);
  }
}

//////////////////////////////////////////////////
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
