# C++の勉強用と自分用のプログラム置き場

## 1	:	GitHubのリポジトリ作成  
#### 1.1	: "New repository"をクリック  
#### 1.2	: "Repository name"にリポジトリ名を設定  
#### 1.3	: "Create repository"をクリック  
#### 1.4	: URLをコピーする  
SSH用URL[SSH_URL]とHTTPS用URL[HTTPS_URL]があるが基本的にSSH用をコピーする  

## 2	:	Gitのリポジトリ作成  
#### 2.1	: 作業用ディレクトリを作成する  
#### 2.2	: WSFL(Windows Subsystem for Linux)のUbuntuを起動して作業用ディレクトリに移動  
/mnt に各ドライブがマウントされている  
#### 2.3	: 移動したら下記コマンドを実行してGitの初期化を行う  
`% git init`  
#### 2.4	: さらに下記コマンドを実行してURLの短縮名を登録する  
`% git remote add [REMOTE_NAME] [SSH_URL]`  
また下記コマンドで短縮名を確認できる  
`% git remote -v`  
#### 2.5	: README.mdファイルを作成する  
内容は適当でよい  

#### 2.6	: 作業が終了したら下記コマンドを実行してバージョン管理の対象として追加する  
`% git add [FILE_NAME]`  
#### 2.7 : 次に下記コマンドを地こうしてコミット[作業結果を確定]させる  
`% git commit -a -m [COMMIT_COMMENT]`  
特定のファイルにコメントを付けたい場合は下記コマンド実行  
`% git commit -m [COMMIT_COMMENT] -- [FILE_NAME]`  
コメントを複数行記入したい場合は以下のコマンドを実行  
`% git commit -- [FILE_NAME]`  

## 3	:	GitHubとGitの連携[ローカル -> リモート]  
#### 3.1	: 作業を終えた際に新規ファイルが存在する場合は2.6～2.7の作業を行う  
#### 3.2	: GitHubとGitの同期を行うために以下のコマンドを実行する  
`% git push -u [REMOTE_NAME] master`  
1度上記コマンドを実行すれば下記コマンドで同期が行える  
`% git push`  
#### 3.3	: ウェブ上で確認を行う  

## 4	:	GitHubとGitの連携[リモート -> ローカル]  
#### 4.1	: GitHubからローカルにダウンロードする際には以下のコマンドを実行する  
`% git pull [REMOTE_NAME] master`  