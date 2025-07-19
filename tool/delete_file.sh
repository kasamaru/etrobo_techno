#!/bin/bash
echo ".identifyファイルを削除しています..."

# ../src内の.identifyファイルを再帰的に削除
find ../src -name "*.identify" -type f -delete -print

echo "処理が完了しました。"
read -p "何かキーを押してください..."