import type { DefaultTheme } from 'vitepress'
import { defineConfig } from 'vitepress'

export const zh = defineConfig({
  lang: 'zh-CN',
  description: 'C 语言笔记',

  themeConfig: {
    nav: nav(),
    sidebar: {
      '/data-structure/': { base: '/data-structure/', items: sidebarDataStructure() },
    },
    socialLinks: [
      { icon: 'github', link: 'https://github.com/zyjared/kit-c' },
    ],

    editLink: {
      pattern: 'https://github.com/zyjared/kit-c/edit/main/docs/:path',
      text: '在 GitHub 上编辑此页',
    },

    footer: {
      message: '基于 MIT 许可发布',
      copyright: `版权所有 © 2024-${new Date().getFullYear()} zyjared`,
    },

    docFooter: {
      prev: '上一页',
      next: '下一页',
    },

    outline: {
      label: '页面导航',
    },

    lastUpdated: {
      text: '最后更新于',
      formatOptions: {
        dateStyle: 'short',
        timeStyle: 'medium',
      },
    },

    langMenuLabel: '多语言',
    returnToTopLabel: '回到顶部',
    sidebarMenuLabel: '菜单',
    darkModeSwitchLabel: '主题',
    lightModeSwitchTitle: '切换到浅色模式',
    darkModeSwitchTitle: '切换到深色模式',
  },

})

function nav(): DefaultTheme.NavItem[] {
  return [
    { text: '首页', link: '/' },
    { text: '数据结构', link: '/data-structure/' },
  ]
}

function sidebarDataStructure(): DefaultTheme.SidebarItem[] {
  return [
    {
      text: '线性表',
      collapsed: false,

      items: [
        { text: '顺序表', link: 'linear-list/sequenatial-list' },
      ],
    },
    {
      text: '栈',
      collapsed: false,
      items: [

      ],
    },
  ]
}
