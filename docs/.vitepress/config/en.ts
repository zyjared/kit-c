import { defineConfig } from 'vitepress'

export const en = defineConfig({
  lang: 'en-US',
  description: 'C language notes',

  themeConfig: {
    editLink: {
      pattern: 'https://github.com/zyjared/kit-c/edit/main/docs/:path',
      text: 'Edit this page on GitHub',
    },

    footer: {
      message: 'Released under the MIT License.',
      copyright: 'Copyright © 2024-present zyjared',
    },
  },
})
