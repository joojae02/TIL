## Infrstructure as Code 도구 테라폼
### IaC란?
> 코드형 인프라 (Infrastructure as Code)는 수동 프로세스가 아닌 코드를 이용해 인프라를 관리하고 프로비저닝하는 것이다

테라폼은 코드로서의 인프라스트럭처 Infrastructure as Code를 지향하고 있는 도구로서,
GUI나 웹 콘솔을 사용해 서비스 실행에 필요한 리소스를 관리하는 대신 필요한 리소스들을 선언적인 코드로 작성해 관리할 수 있게 해준다

그냥 코드로 인프라 관리하기

![](https://i.imgur.com/L6dXKU0.png)

Terraform은 Hashicorp에서 오픈소스로 개발중인 인프라스트럭처 관리 도구이다.

서비스 실행에 필요한 환경을 구축하는 도구라는 점에서 Chef, Ansible 같은 설정 관리 도구와 더불어 프로비저닝 도구이다

## 왜 쓰지
#### 자동화

- 수동으로 서버를 생성하는게 아니라 코드로 생성 하기 때문에 서버 운영및 관리가 모두 자동화 될 수 있다. 
- 예를 들어, AWS에서 새로운 서버를 생성 하기 위해서 AWS 콘솔에 로그인 할 필요도 없이 terraform 코드를 실행시키기만 하면 된다.

#### 속도 와 안전

- 코드로 실행 되기 때문에 사람이 수동으로 작업하는것 보다 훨씬 빠르며 또한 사람이 직접 할 때 생길수 있는 실수 들을 방지할수 있다.

#### 문서화

- 모든 인프라가 코드로 기록 및 관리 되기 때문에 자동으로 문서화가 된다.
- terraform의 경우에는 새로 들어온 개발자 라도 terraform code를 보면 전체적인 구성을 이해할수 있다.

#### 형상관리

- 여느 코드와 마찬가지로 terraform 코드도 git 등등을 이용해 형상관리를 할수 있다.
- 인프라의 변경 기록을 쉽게 볼수 있다.

#### 리뷰 및 테스트

- terraform 코드도 리뷰 및 테스트가 가능하다.
- terraform의 경우 코드 리뷰와 테스트를 통해 문제가 실제로 발생되는 것을 어느정도 예방할수 있다.

#### Reuse

- 역시 여느 코드와 마찬가지로 reuse가 가능하다. 한번 terraform 코드를 사용해서 인프라를 구축해놓으면 그 후 새로 추가하는 인프라들을 구성하기가 쉬워진다.


## 프로비저닝 vs. 배포 vs. 오케스트레이션

### 프로비저닝

시스템, 데이터 및 소프트웨어로 서버를 준비하고 네트워크 작동을 준비
Puppet, Ansible, terraform 등과 같은 구성 관리 도구를 사용하여 서버를 프로비저닝할 수 있다
이처럼, 클라우드 서비스를 시작하고 구성하는 것을 "프로비저닝"한다고 한다

### 배포

배포는 프로비저닝된 서버를 실행하기 위해 애플리케이션 버전을 제공하는 작업이다
지속적 배포는 AWS CodePipeline, Jenkins, Github Actions등을 이용할 수 있다

### 오케스트레이션

오케스트레이션은 여러 시스템 또는 서비스를 조정하는 작업이다
마이크로서비스, 컨테이너 및 Kubernetes로 작업할 때 일반적인 용어이다

## Configuration Drift
> 예상치 못한 인프라 변경에 대한 사고와 미치는 영향을 칭한다
#### AWS Config
잘못 설정된 것을 찾기 위한 도구로서, 바른 설정을 지정해놓고 찾아서 고칠 수 있게 만들어준다.

#### AWS CloudFormation Drift Detection

사고 감지를 위한 도구로서, 스택에서 드리프트 감지 작업을 수행하면 스택이 예정 템플릿 구성에서 드리프트되었는지 확인
드리프트 감지를 지원하는 스택의 각 리소스에 대한 드리프트 상태 관련 세부 정보를 반환한다.

#### Terraform state files

위와 같은 관리형 서비스 보다 개발 방법에 가까운 솔루션이다
**정상 작동 상태**를 파일로 저장하고, **상태 정의된 파일**은 인프라의 **실제 상태**와의 비교 대상으로서 현재 상황을 진단/점검할 수 있습니다.

## 테라폼의 기본 개념들

### 프로비저닝
> 어떤 프로세스나 서비스를 실행하기 위한 준비 단계를 프로비저닝이라 한다

테라폼에선 주로 컴퓨팅 자원을 준비하는 작업을 의미한다

### 프로바이더
> 테라폼과 외부 서비스를 연결해주는 기능을 하는 모듈

```
provider "aws" {
	region = "ap-northeast-2"
	
}
```

프로바이더로는 다음과 같이 매우 많다 전체는 문서에서
- AWS
- 구글 클라우드
- 마이크로소프트 애저
- 깃허브 
- MySQL
- 레빗
- 도커
[테라폼 프로바이더 문서](https://www.terraform.io/docs/providers/index.html)

### 모듈
> 관련 리소스 그룹을 단일 리소스 처럼 관리할 수 있는 재사용 가능한 구성

```
module "vpc" {
	source = "terraform-aws-modules/vpc/aws"
	version = "~> 3.0"

	name = local.name
	...
}
```
### 리소스
> 특정 프로바이더가 제공해주는 조작 가능한 대상의 최소 단위

AWS 프로바이더는 `aws_instance` 리소스 타입을 제공하고
이 **리소스 타입**을 사용해 Amazon EC2의 가상 머신 **리소스**를 선언하고 조작하는 것이 가능하다
EC2 인스턴스, 시큐리티 그룹, 키 페어 모두 `aws` 프로바이더가 제공해주는 리소스 타입이다

```
resource "aws_instance" "sample" {
	ami = "~"
	instance_type = "~"
	...
}
```

### HCL
> 테라폼에서 사용하는 설정 언어

테라폼에서 모든 설정과 리소스 선언은 HCL을 사용해 이루어진다
확장자는 `.tf`

### 계획 (Plan)
> 테라폼 프로젝트 디렉터리 아래의 모든 `.tf` 파일의 내용을 실제로 적용 가능한지 확인하는 작업

테라폼은 이를 `terraform plan` 명령어로 제공하며, 
이 명령어를 실행하면 어떤 리소스가 생성되고, 수정되고, 삭제될지 계획을 보여준다

### 적용 (Apply)
> 프로젝트 디렉터리 아래의 모든 `.tf` 파일의 내용대로 리소스를 생성, 수정, 삭제하는 일을 적용하는 일

명령어를 실행하기 전에 변경 예정 사항은 `plan` 명령어를 사용해 확인할 수 있다
적용하기 전에도 플랜의 결과를 보여준다

## 테라폼으로 aws 해보자

- **1단계** - 먼저 아마존 웹 서비스 계정을 준비하고, API 키를 설정합니다.
- **2단계 - 1** - 인프라스트럭처를 정의하는 HCL 언어로 필요한 리소스를 선언합니다.
- **2단계 - 2** - 선언된 리소스들이 생성가능한지 계획(Plan)을 확인합니다.
- **2단계 - 3** - 선언된 리소스들을 아마존 웹 서비스에 적용(Apply)합니다.
- **3단계** - 웹 애플리케이션을 배포합니다.

## 설치하기
```bash
brew install terraform
brew install awscli
```

안된다면..
- [테라폼 다운](https://developer.hashicorp.com/terraform/downloads)
- 여기서 ARM64 다운 압축 풀고 `/usr/local/bin/`여기로 옮겨주자

## 1단계 IAM 생성
- 이름은 대충 아무거나

![](https://i.imgur.com/Jg2WDLx.png)


- `AdministratorAccess`
- 루트권한
- 사실 사용하는 서비스 따라서 설정해주는게 좋은데..
- 일단 루트로

![](https://i.imgur.com/wlAvdwG.png)

그리고 생성

![](https://i.imgur.com/7q4mFBG.png)

![](https://i.imgur.com/A7i0cUT.png)

그리고 보안 자격 증명으로
![](https://i.imgur.com/XTvv1Bv.png)


![](https://i.imgur.com/LKDAiNj.png)


이때 만든 access키는 잘 보관하고 있자

터미널에서 명령어로 엑세스 키 등록하기
```
aws configure
```
- 이걸로 정상적으로 들어갔는지 확인
```
cat ~/.aws/credentials
```

## 2단계 HCL로 리소스 정의하고 AWS에 프로비저닝

1. 인프라스트럭처를 정의하는 HCL 언어로 필요한 리소스를 선언
2. 선언된 리소스들이 생성가능한지 계획(Plan)을 확인
3. 선언된 리소스들을 아마존 웹 서비스에 적용(Apply)

EC2와 RDS 리소스를 생성하기 위해 4개의 리소스 정의
- `aws_key_pair`
- `aws_security_group`
- `aws_instance`
- `aws_db_instance`

일단 아무 디렉토리나 만들고
```
touch provider.tf web_infra.tf
```
테라폼은 기본적으로 특정 디렉터리에 있는 모든 `.tf` 확장자를 가진 파일을 전부 읽어들인 후, 리소스 생성, 수정, 삭제 작업을 진행한다
그래서 이름은 자유롭게

- `provider.tf`
```
provider "aws" { 
	// aws configure 했다면 생략 가능
	access_key = "<AWS_ACCESS_KEY>"
	secret_key = "<AWS_SECRET_KEY>"

	region = "ap-northeast-2"
}
```

기본적으로 provider는
```
provider "<PROVIDER_NAME>" { 
	<ATTR_NAME> = "<ATTR_VALUE>" 
}
```
이런 구조를 가짐

그리고 해당 디렉토리에서 다음 명령어 실행
```
terraform init
```

#### HCL 언어로 필요한 리소스를 정의

`web_infra.tf`에 써주기
```
resource "aws_key_pair" "web_admin" {
  key_name = "web_admin"
  public_key = "<PUBLIC_KEY>"
}
```

`resource` 키워드 다음에 `"aws_key_pair" "web_admin"`과 같이 두 개의 문자열이 온다

첫 번째 문자열은 **리소스 타입**의 이름
리소스 이름에서는 관습적으로 프로바이더 이름에 언더스코어 붙여 전치사(prefix)로 사용한다

`aws_key_pair`에서 `aws` 프로바이더가 제공하는 `key_pair` 리소스라는 것

두 번째 문자열 `web_admin`은 이 리소스에 임의로 붙이는 이름
나중에 이 리소스를 참조하기 위해 이름 붙여주기

> 여기서 지정하는 이름은 AWS에서 사용하는 이름이 아니다
> 참조하기 위해 사용하는 이름임

`key_name`은 AWS 상에 현재 정의하는 키 페어를 등록할 이름
`public_key`에는 접속에 사용할 공개키의 값
- 미리 생성했던 SSH 키 넣어도 됨
- 없다면 새로 만들자
- 
```
$ ssh-keygen -t rsa -b 4096 -C "<EMAIL_ADDRESS>" -f "$HOME/.ssh/web_admin" -N ""
```

복붙하면 너무 기니까 이렇게 넣어도 무방
```
public_key = file("~/.ssh/<공개키이름>.pub")
```

#### 선언한 리소스들이 생성가능한지 계획(Plan)을 확인

```
$ terraform plan

Terraform will perform the following actions:

  # aws_key_pair.web_admin will be created
  + resource "aws_key_pair" "web_admin" {
      + arn             = (known after apply)
      + fingerprint     = (known after apply)
      + id              = (known after apply)
      + key_name        = "web_admin"
      + key_name_prefix = (known after apply)
      + key_pair_id     = (known after apply)
      + key_type        = (known after apply)
      + public_key      = "ssh-rsa ~~"
      + tags_all        = (known after apply)
    }

```

이런 느낌으로 결과가 출력된다

>테라폼 앞에 있는 `+` 문자는 ’`aws_key_pair.wed_admin` 리소스를 생성하겠다’는 의미

#### `plan`의 작동 방식
테라폼에서 리소스는 선언적으로 쓴다

 `.tf` 파일에 기술되어있는 모든 리소스를 읽어들이고 먼저 이 리소스들이 존재하는 상태를 가정한다

테라폼의 가장 중요한 역할은 이 상태를 실제 AWS 계정 내 실제 상태로 올리는 것이다.
이를 적용(Apply)한다고 표현한다

따라서 계획(Plan)에서 `+ resource "aws_key_pair" "web_admin"`는 생성 예정 상태인것이다

#### 선언된 리소스들을 아마존 웹 서비스에 적용(Apply)


```
> terraform apply
  # aws_key_pair.web_admin will be created
  + resource "aws_key_pair" "web_admin" {
      + arn             = (known after apply)
      + fingerprint     = (known after apply)
      + id              = (known after apply)
      + key_name        = "web_admin"
      + key_name_prefix = (known after apply)
      + key_pair_id     = (known after apply)
      + key_type        = (known after apply)
      + public_key      = "ssh-rsa~"
      + tags_all        = (known after apply)
    }

Plan: 1 to add, 0 to change, 0 to destroy.

Do you want to perform these actions?
  Terraform will perform the actions described above.
  Only 'yes' will be accepted to approve.

  Enter a value: yes

aws_key_pair.web_admin: Creating...
aws_key_pair.web_ad
min: Creation complete after 0s [id=web_admin]

Apply complete! Resources: 1 added, 0 changed, 0 destroyed.
```
현재는 리소스를 생성하기 전에 `plan` 결과를 보여주고 `yes`를 입력해야만 리소스를 생성한다.
`yes` 입력

![](https://i.imgur.com/rzQA5gi.png)

ec2 키 페어에 생성된것을 볼 수 있다

```
> terraform plan 
aws_key_pair.web_admin: Refreshing state... [id=web_admin]

No changes. Your infrastructure matches the configuration.

Terraform has compared your real infrastructure against your configuration and found no differences, so no changes are needed.
```

다시 `terraform plan`을 해보면 plan상태와 실제 상태의 차이가 없어 변경할 게 없다고 나온다
### 두 번째 이터레이션: SSH 접속 허용을 위한 시큐리티 그룹
다음은  `aws_security_group` 리소스다
인스턴스를 생성해도 밖에서 접근할 수 있는 방법이 없다면 사용할 수가 없기에 포트를 열어주는 보안 그룹을 만들어야 된다

`web_infra.tf`아래에
```
resource "aws_security_group" "ssh" { 
	name = "allow_ssh_from_all"
	description = "Allow SSH port from all" 
	ingress { 
		from_port = 22 
		to_port = 22 
		protocol = "tcp" 
		cidr_blocks = ["0.0.0.0/0"] 
	}
}
```
`name`과 `description`에는 각각 시큐리티 그룹의 이름과 설명을 기입한다.
- `ingress`는 인바운드 트래픽을 정의하는 속성
-  `egress`라는 아웃바운드 트래픽 정의 속성도 사용 가능

그 다음에 `plan` 
```
> terraform plan

Terraform used the selected providers to generate the following execution plan. Resource actions are indicated with the following
symbols:
  + create

Terraform will perform the following actions:

  # aws_security_group.ssh will be created
  + resource "aws_security_group" "ssh" {
      + arn                    = (known after apply)
      + description            = "Allow SSH port from all"
      + egress                 = (known after apply)
      + id                     = (known after apply)
      + ingress                = [
          + {
              + cidr_blocks      = [
                  + "0.0.0.0/0",
                ]
              + description      = ""
              + from_port        = 22
              + ipv6_cidr_blocks = []
              + prefix_list_ids  = []
              + protocol         = "tcp"
              + security_groups  = []
              + self             = false
              + to_port          = 22
            },
        ]
      + name                   = "allow_ssh_from_all"
      + name_prefix            = (known after apply)
      + owner_id               = (known after apply)
      + revoke_rules_on_delete = false
      + tags_all               = (known after apply)
      + vpc_id                 = (known after apply)
    }

Plan: 1 to add, 0 to change, 0 to destroy.
```
내용 확인후 `apply`한다

### 세 번째 이터레이션: EC2 인스턴스 정의


키 페어와 시큐리티 그룹을 사용해 EC2 인스턴스를 정의할 차례이지만

VPC의 기본(default) 시큐리티 그룹을 불러와야 한다

```
data "aws_security_group" "default" {
	name = "default"
}
```

속정으로 `id = "<SECURITY_GROUP_ID>"` 로 특정 시큐리티 그룹을 참조할수 있다.

다음으로 ec2 리소스 

```
resource "aws_instance" "web" {
	ami = "ami-0c9c942bd7bf113a2" # Ubuntu Server 22.04 LTS
	instance_type = "t2.micro"
	key_name = aws_key_pair.web_admin.key_name 
	vpc_security_group_ids = [
		aws_security_group.ssh.id,
		data.aws_security_group.default.id 
	]
}
```

- `key_name`에는 EC2 키 페어의 이름을 지정
- `vpc_security_group_ids`
	- `ssh` 시큐리티 그룹의 `id` 속성을 참조
	- `default` 데이터 소스의 `id` 속성을 참조

이후 똑같이 `plan` 확인 후 `apply` 해주기


![](https://i.imgur.com/GbWShDC.png)

다음으로 해당 서버의 주소를 확인한다

```
$ terraform console
> aws_instance.web.public_ip
"<ec2 ip 주소>"
```

```
$ ssh -i ~/.ssh/<비밀키> ec2-user@<ec2 ip 주소>
```

```
The authenticity of host '<주소> (<주소>)' can't be established.
This key is not known by any other names
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
Warning: Permanently added '<주소>' (ED25519) to the list of known hosts.

       __|  __|_  )
       _|  (     /   Amazon Linux 2 AMI
      ___|\___|___|

https://aws.amazon.com/amazon-linux-2/
55 package(s) needed for security, out of 132 available
Run "sudo yum update" to apply all updates.
```


#### RDS 인스턴스 정의
```
resource "aws_db_instance" "web_db" {
	allocated_storage = 8
	engine = "mysql"	
	engine_version = "8.0.33"
	instance_class = "db.t2.micro"
	username = "admin"
	password = "test_password"
	skip_final_snapshot = true
}
```

다시 `plan`실행
정상적으로 실행된다면
`terraform apply`

```
$ terraform console
> aws_db_instance.web_db.endpoint
<db_instance endpoint>
```

다음 ssh 접속
```
$ ssh -i ~/.ssh/<비밀키> ec2-user@<ec2 ip 주소>
```
mysql 설치
```
$ sudo yum install -y mysql

$ $ mysql -h <dp_endpoint> -u admin -p

```

접속 되면? 성공

마지막으로 다 했다면..? 지워주도록 하자
```
$ terraform destroy
```

### 전체 코드
```
// provider.tf
provider "aws" {

	region = "ap-northeast-2"

}


// web_infra.tf
resource "aws_key_pair" "web_admin" {

	key_name = "web_admin"
	
	public_key = file("~/.ssh/web_admin.pub")

}

  

resource "aws_security_group" "ssh" {

	name = "allow_ssh_from_all"
	
	description = "Allow SSH port from all"
	
	ingress {
		
		from_port = 22
		
		to_port = 22
		
		protocol = "tcp"
		
		cidr_blocks = ["0.0.0.0/0"]
	
	}

}

  

data "aws_security_group" "default" {

	name = "default"

}

  

resource "aws_instance" "web" {

	ami = "ami-0a93a08544874b3b7" # amzn2-ami-hvm-2.0.20200207.1-x86_64-gp2
	
	instance_type = "t2.micro"
	
	key_name = aws_key_pair.web_admin.key_name
	
	vpc_security_group_ids = [
	
		aws_security_group.ssh.id,
		
		data.aws_security_group.default.id
		
	]

}

  

resource "aws_db_instance" "web_db" {

	allocated_storage = 8
	
	engine = "mysql"
	
	engine_version = "8.0.33"
	
	instance_class = "db.t2.micro"
	
	username = "admin"
	
	password = "test_password"
	
	skip_final_snapshot = true

}
```
### 참고
- [테라폼 소개](https://rampart81.github.io/post/what-is-terraform/)
- [Terraform 개념 잡기](https://insight.infograb.net/blog/2023/01/25/terraform-basic/)
- [Terraform 101](https://mooyoul.github.io/2016/12/19/Terraform-101/terraform.png "Terraform")
- [테라폼 튜토리얼](https://www.44bits.io/ko/post/terraform_introduction_infrastrucute_as_code#%EB%93%A4%EC%96%B4%EA%B0%80%EB%A9%B0-infrstructure-as-code-%EB%8F%84%EA%B5%AC-%ED%85%8C%EB%9D%BC%ED%8F%BCterraform)

- [테라폼 공식 문서](https://www.terraform.io/docs/index.html)
- [테라폼 명령어 - plan](https://www.terraform.io/docs/commands/plan.html)
- [테라폼 명령어 - apply](https://www.terraform.io/docs/commands/apply.html)
- [테라폼 명령어 - console](https://www.terraform.io/docs/commands/console.html)
### 테라폼 - AWS 프로바이더 레퍼런스

- [AWS 프로바이더: aws](https://www.terraform.io/docs/providers/aws/)
- [AWS 리소스: aws_key_pair](https://www.terraform.io/docs/providers/aws/r/key_pair.html)
- [AWS 데이터 소스: aws_security_group](https://www.terraform.io/docs/providers/aws/d/security_group.html)
- [AWS 리소스: aws_security_group](https://www.terraform.io/docs/providers/aws/r/security_group.html)
- [AWS 리소스: aws_instance](https://www.terraform.io/docs/providers/aws/r/instance.html)
